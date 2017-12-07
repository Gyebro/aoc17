#include "days.h"

#ifndef TODAY_ONLY

int day01_a(string s) {
    int sum = 0;
    size_t len = s.size();
    for (size_t i=0; i<len-1; i++) {
        if (s[i] == s[i+1]) { sum += s[i]-'0'; }
    }
    if (s[0] == s[len-1]) { sum += s[len-1]-'0'; }
    return sum;
}

int day01_b(string s) {
    int sum = 0;
    size_t len = s.size();
    size_t step = len/2;
    for (size_t i=0; i<len-step; i++) {
        if (s[i] == s[i+step]) { sum += s[i]-'0'; }
    }
    for (size_t j=len-step; j<len; j++) {
        if (s[j] == s[j-step]) { sum += s[j]-'0'; }
    }
    return sum;
}

int day02_a(string s, char delim) {
    vector<string> lines = split(s, '\n');
    int checksum = 0;
    for (const string &line : lines) {
        vector<string> cells = split(line, delim);
        int min = stoi(cells[0]);
        int max = min;
        for (const string &c : cells) {
            int val = stoi(c);
            if(val < min) min = val;
            if(val > max) max = val;
        }
        checksum += (max-min);
    }
    return checksum;
}

int day02_b(string s, char delim) {
    vector<string> lines = split(s, '\n');
    int checksum = 0;
    for (const string &line : lines) {
        vector<string> cells = split(line, delim);
        vector<int> numbers;
        numbers.reserve(cells.size());
        for (const string &c : cells) { numbers.push_back(stoi(c)); }
        for (size_t i=1; i<numbers.size(); i++) {
            int a = numbers[i];
            for (size_t j=0; j<i; j++) {
                int b = numbers[j];
                int big = max(a,b); int small = min(a,b);
                if (big % small == 0) {
                    checksum += big/small;
                }
            }
        }
    }
    return checksum;
}

/**
 * Return the distance of square at address from the center of the spiral
 * Spiral structure looks like this
 * 17  16  15  14  13
 * 18  5   4   3   12
 * 19  6   1   2   11
 * 20  7   8   9   10
 * 21  22  23  23  .. ..
 * Let's say the squares are in disks in annuli,
 * First one contains 1, (n=1)
 * Second one 1+1...3^2  (n=3)
 * Third: 3^2+1...5^2    (n=5)
 * Each annulus can be divided into four quadrants
 * For example: third one (n=5) contains 4*(n-1) = 16 numbers
 * In every quadrant, the manhattan distance from the origin is
 *  d = (n-1)/2 + abs(i - (n-1)/2),
 * where i is the index of the square in the quadrant
 * @param address Address of square whose distance is returned
 * @return Manhattan distance from '1'
 */
long int day03_a(long int address) {
    // Find n
    long int r = (long int)floor(sqrt((double)address));
    if (r%2 == 0) r--;
    long int n = r+2; // Odd
    // The quadrant size of annulus n is q = n-1
    long int q = n-1; // Even
    // Find the index of the address in its quadrant
    long int i = (address-r*r)%q;
    // Find the distance
    return q/2 + abs(i-q/2);
}

// Generate spiral up to address
struct day03_square {
    long int i; // x-coordinate
    long int j; // y-coordinate
    long int a; // address
    long int v; // value
};

long int day03_find_value(const vector<day03_square>& squares, long int i, long int j) {
    for (const day03_square& s : squares) {
        if (s.i == i && s.j == j) {
            return s.v;
        }
    }
    return 0;
}

long int day03_b(long int address) {
    vector<day03_square> squares;
    day03_square s = {0,0,1,1};
    squares.push_back(s);
    long int r = 1;
    long int n = r+2;
    long int v = 1;
    while (v < address) {
        // Quadrant size at next annuli
        long int q = n-1;
        // Start filling up the next annuli
        s.i++;
        for (long int i=1; i<=n*n-r*r; i++) {
            s.a = r*r+i;
            // Gather the neighbours (brute force way)
            // TODO: Optimize this
            s.v = 0;
            s.v += day03_find_value(squares, s.i-1, s.j-1);
            s.v += day03_find_value(squares, s.i-1, s.j  );
            s.v += day03_find_value(squares, s.i-1, s.j+1);
            s.v += day03_find_value(squares, s.i  , s.j-1);
            s.v += day03_find_value(squares, s.i  , s.j+1);
            s.v += day03_find_value(squares, s.i+1, s.j-1);
            s.v += day03_find_value(squares, s.i+1, s.j  );
            s.v += day03_find_value(squares, s.i+1, s.j+1);
            squares.push_back(s);
            v = s.v;
            if (v > address) break;
            //cout << "square: (" << s.i << "," << s.j << ") = " << s.a << ", " << s.v << endl;
            long int qi = i/q;
            // Step to next
            switch (qi) {
                case 0:
                    s.j++; break;
                case 1:
                    s.i--; break;
                case 2:
                    s.j--; break;
                case 3:
                    s.i++; break;
            }
        }
        r+=2;
        n+=2;
    }
    return v;
}

size_t day04_a(string pplist) {
    size_t validCount = 0;
    vector<string> pps = split(pplist, '\n');
    for (const string &pp : pps) {
        bool valid = true;
        vector<string> parts = split(pp, ' ');
        for (size_t i=1; i<parts.size(); i++) {
            string tested = parts[i];
            for (size_t j=0; j<i; j++) {
                if (parts[j] == tested) { valid = false; }
            }
            if (!valid) break;
        }
        if (valid) validCount++;
    }
    return validCount;
}

size_t day04_b(string pplist) {
    size_t validCount = 0;
    vector<string> pps = split(pplist, '\n');
    for (const string &pp : pps) {
        bool valid = true;
        vector<string> parts = split(pp, ' ');
        // Test current passphrase
        for (size_t i=1; i<parts.size(); i++) {
            string tested = parts[i];
            // Test with all previous words
            for (size_t j=0; j<i; j++) {
                if (anagram_pair_test(parts[j], tested)) { valid = false; }
            }
            if (!valid) break;
        }
        if (valid) validCount++;
    }
    return validCount;
}

size_t day05_a(string s, bool part_two) {
    vector<string> i_strings = split(s, '\n');
    vector<int> instructions;
    instructions.reserve(i_strings.size());
    for (const string& i : i_strings) {
        instructions.push_back(stoi(i));
    }
    // Start running
    int pointer = 0;
    int size = (int)instructions.size();
    int jump = 0;
    size_t steps = 0;
    while ((0 <= pointer) && (pointer < size)) {
        jump = instructions[pointer];
        if (!part_two) {
            instructions[pointer]++;
        } else {
            jump>=3 ? instructions[pointer]-- : instructions[pointer]++;
        }

        pointer += jump;
        steps++;
    }
    return steps;
}

size_t day06_a(string s, bool part_two) {
    vector<string> block_strings = split(s, '\t');
    vector<size_t> banks; banks.reserve(block_strings.size());
    for (const string& b : block_strings) {
        banks.push_back(stoul(b));
    }
    // Run the redistribution
    size_t steps = 0;
    size_t i = 0;
    size_t len = banks.size();
    size_t d = 0;
    vector< vector< size_t> > history;
    history.push_back(banks);
    while (true) {
        steps++;
        i = max_idx(banks);
        d = banks[i];
        banks[i] = 0;
        for (size_t j=0; j<d; j++) {
            i++;
            if (i>=len) i-=len;
            banks[i]++;
        }
        // Compare with all previous
        size_t history_idx = 0;
        for (const vector<size_t>& h: history ) {
            bool same = true;
            for (size_t k=0; k<len; k++) {
                if (h[k] != banks[k]) {
                    same = false;
                    break;
                }
            }
            if (same) {
                if (!part_two) {
                    return steps;
                } else {
                    return steps-history_idx;
                }
            }
            history_idx++;
        }
        history.push_back(banks);
    }
    return 0;
}

#endif //TODAY_ONLY

struct day07_node {
    string name;
    int value;
    int sum;
    bool has_parent;
    vector<string> children;
    size_t parent_idx;
};

size_t day07_find_name(const vector<day07_node>& g, const string& name) {
    for (size_t j=0; j<g.size(); j++) {
        if (g[j].name == name) {
            return j;
        }
    }
    cout << "ERROR!\n";
    return -1;
}

// Recursively updates the sum of nodes
int day07_update_sum(vector<day07_node>& g, const size_t idx) {
    if (g[idx].children.size() == 0) {
        g[idx].sum = g[idx].value;
        return g[idx].sum;
    } else {
        int total = g[idx].value;
        for (const string& child : g[idx].children) {
            // Child idx
            const size_t child_idx = day07_find_name(g, child);
            total += day07_update_sum(g, child_idx);
        }
        g[idx].sum = total;
        return total;
    }
}

// Recursively find the unbalanced node
int day07_find_fault(vector<day07_node>& g, const size_t idx, const int diff=0) {
    if (g[idx].children.size() == 0) {
        return 0;
    } else {
        vector<int> sums;
        for (const string& child : g[idx].children) {
            const size_t child_idx = day07_find_name(g, child);
            sums.push_back(g[child_idx].sum);
        }
        int sfirst = sums[0];
        // Either sfirst differs from the others or one other is different
        size_t diffs = 0;
        for (size_t j=1; j<sums.size(); j++) {
            if (sums[j] != sfirst) {
                diffs++;
                cout << "Child '" << g[idx].children[j] << "' has different sum: " << sums[j] <<
                     " (expected: " << sfirst << ", diff: " << sfirst-sums[j] << ")\n";
                // child j is the faulty, investigate
                const size_t child_idx = day07_find_name(g, g[idx].children[j]);
                day07_find_fault(g, child_idx, sfirst-sums[j]);
            }
        }
        if (diffs == 0) {
            cout << "All children of '" << g[idx].name << "' are balanced, apply the diff here!\n";
            cout << "Change value from '" << g[idx].value << "' to '" << g[idx].value+diff << "'.\n";
        }
    }
}

void day07_a(string s, bool part_two) {
    // Build tree graph
    vector<day07_node> g;
    day07_node n;
    vector<string> node_strings = split(s, '\n');
    vector<string> parts;
    vector<string> items;
    for (const string& node_string : node_strings) {
        // Split around '->'
        parts = split(node_string, '-');
        if (parts.size() > 1) {
            // This line had "->" in it, start building up the node
            items = split(parts[0], ' ');
            n.name = items[0];
            n.value = stoi(items[1].substr(1, items[1].size()-2));
            vector<string> ch;
            for (const string& c : split(parts[1].substr(2, parts[1].size()-2), ',')) {
                ch.push_back(trim_spaces(c));
            }
            n.children = ch;
            g.push_back(n);
        } else {
            // Its a single terminal node
            items = split(parts[0], ' ');
            n.name = items[0];
            n.value = stoi(items[1].substr(1, items[1].size()-2));
            vector<string> ch; ch.resize(0);
            n.children = ch;
            g.push_back(n);
        }
        //cout << "Added node: name: " << n.name << ", val: " << n.value << ", ch count: " << n.children.size() << endl;
    }
    // Set child indices and root flags
    for (size_t i=0; i<g.size(); i++) {
        if (g[i].children.size() > 0) {
            for (string child : g[i].children) {
                size_t j = day07_find_name(g, child);
                g[j].parent_idx = i;
                g[j].has_parent = true;
            }
        }
    }
    // Find the nodes without parent
    string root_name;
    for (const day07_node& ni : g) {
        if (!ni.has_parent) {
            cout << "'" << ni.name << "' doesn't have parent, it is the root node!\n";
            root_name = ni.name;
        }
    }
    if (part_two) {
        size_t root_idx = day07_find_name(g, root_name);
        // Update sums
        size_t all_sum = day07_update_sum(g, root_idx);
        cout << "Fun fact: sum of whole graph is " << all_sum << ".\n";
        // Check balances
        size_t unbalanced_idx = 0;
        for (size_t i=0; i<g.size(); i++) {
            if (g[i].children.size() == 0) {
                // Terminal node balanced always
            } else {
                bool balanced = true;
                vector<int> sums;
                for (const string& child : g[i].children) {
                    const size_t child_idx = day07_find_name(g, child);
                    sums.push_back(g[child_idx].sum);
                }
                // Check if all values are the same
                int sfirst = sums[0];
                size_t diffs = 0;
                for (size_t j=1; j<sums.size(); j++) {
                    if (sums[j] != sfirst) {
                        balanced = false;
                        diffs++;
                    }
                }
                if (!balanced & (diffs==1)) {
                    cout << "Node '" << g[i].name << "' is not balanced! It's index is: '" << i << "'.\n";
                    unbalanced_idx = i;
                    break;
                }
            }
        }
        // Check who needs to be fixed
        day07_find_fault(g, unbalanced_idx);
    }
}
