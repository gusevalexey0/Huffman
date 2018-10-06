
#include <iostream>
#include "compression.h"
#include "lib/BinaryTrie.h"

std::vector<uint64_t> buildCodes(std::vector<unsigned char> const &lens) {
    std::vector<std::pair<unsigned char, unsigned char> > length(256);
    unsigned char i = 0;
    do {
        length[i] = { lens[i], i };
    } while (++i != 0);
    std::sort(length.begin(), length.end());
    std::vector<uint64_t> codes(256);
    uint64_t cur_code = 0;
    codes[length[0].second] = 0;
    for (unsigned char i = 1; i != 0; ++i) {
        ++cur_code;
        cur_code <<= (length[i].first - length[i - 1].first);
        codes[length[i].second] = cur_code;
    }
    return codes;
}


void countLens(size_t v, unsigned char d, std::vector<node> const &tree, std::vector<unsigned char> &lens) {
    if (tree[v].left == node::nullpointer && tree[v].right == node::nullpointer) {
        lens[v] = d;
        return;
    }

    if (tree[v].left != node::nullpointer) {
        countLens(tree[v].left, d + 1, tree, lens);
    }
    if (tree[v].right != node::nullpointer) {
        countLens(tree[v].right, d + 1, tree, lens);
    }
}


void encode(std::istream &input, std::ostream &output) {
    BufferedReader in(input);
    BufferedWriter out(output);
    uint64_t freq[256] = {};
    unsigned char c;
    while (in.read(c)) {
        freq[c]++;
    }
    in.reset();


    std::vector<node> tree(511);
    std::priority_queue<std::pair<uint64_t, uint16_t>, std::vector<std::pair<uint64_t, uint16_t> >, std::greater<std::pair<uint64_t, uint16_t>>> queue; //второе - индекс в tree
    uint16_t cnt_nodes = 0;
    for (; cnt_nodes < 256; ++cnt_nodes) {
        queue.push({ freq[cnt_nodes], cnt_nodes });
    }

    while (cnt_nodes < 511) {
        std::pair<uint64_t, uint16_t> node1 = queue.top();
        queue.pop();
        std::pair<uint64_t, uint16_t> node2 = queue.top();
        queue.pop();
        tree[cnt_nodes] = { node1.second, node2.second };
        queue.push({ node1.first + node2.first, cnt_nodes });
        ++cnt_nodes;
    }
    std::vector<unsigned char> lens(256);
    countLens(510, 0, tree, lens);

    std::vector<uint64_t> codes = buildCodes(lens);

    unsigned char special = 0;
    unsigned char i = 0;
    do {
        special = (special + (lens[i] * freq[i]) % 8 ) % 8;
    } while (++i != 0);

    out.write(special);

    for (auto code : lens) {
        out.write(code);
    }

    unsigned char tmp = 0;
    int tmp_size = 0;
    while (in.read(c)) {
        for (unsigned char j = lens[c]; j-- > 0;) {
            if (tmp_size == 8) {
                out.write(tmp);
                tmp_size = 0;
                tmp = 0;
            }
            bool bit = codes[c] & (1ULL << j);
            tmp |= bit << (7 - tmp_size);
            ++tmp_size;
        }
    }
    out.write(tmp);
}

void decode(std::istream &input, std::ostream &output) {
	BufferedReader in(input);
	BufferedWriter out(output);

	unsigned char special;
	in.read(special);

	std::vector<unsigned char> lens(256);

    for (auto &l : lens) {
        in.read(l);
    }
	std::vector<uint64_t> codes = buildCodes(lens);
	BinaryTrie trie(codes, lens);

	unsigned char cur, nxt = '!';
	in.read(cur);
	bool last_time = true, succ;
	int CONDITION = 0;
	while ((succ = in.read(nxt)) || last_time) {
		if (!succ) {
			if (special == 0 && nxt != '!')
			    special = 8;
			last_time = false;
			CONDITION = 8 - special;
		}
		for (int j = 7; j >= CONDITION; --j) {
			bool direction = cur & (1 << j);
			trie.step(direction);
			if (trie.isTerminal()) {
				out.write(trie.getChar());
				trie.reset();
			}
		}
		cur = nxt;
		nxt = '?';
	}
}
