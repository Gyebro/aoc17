#include <c++/bitset>
#include <c++/queue>
#include <c++/list>
#include "macros.h"
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
    if (!part_two) {
        while ((0 <= pointer) && (pointer < size)) {
            jump = instructions[pointer];
            instructions[pointer]++;
            pointer += jump;
            steps++;
        }
    } else {
        // Part two
        while ((0 <= pointer) && (pointer < size)) {
            jump = instructions[pointer];
            jump>=3 ? instructions[pointer]-- : instructions[pointer]++;
            pointer += jump;
            steps++;
        }
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

struct day07_node {
    string name;
    int value;
    int sum;
    bool has_parent;
    vector<string> children;
    vector<size_t> children_idx;
    size_t parent_idx;
};

size_t day07_find_name(const vector<day07_node>& g, const string& name) {
    for (size_t j=0; j<g.size(); j++) {
        if (g[j].name == name) {
            return j;
        }
    }
    cout << "ERROR! Cannot find: '" << name << "' \n";
    return -1;
}

// Recursively updates the sum of nodes
int day07_update_sum(vector<day07_node>& g, const size_t idx) {
    if (g[idx].children.size() == 0) {
        g[idx].sum = g[idx].value;
        return g[idx].sum;
    } else {
        int total = g[idx].value;
        for (const size_t& child_idx : g[idx].children_idx) {
            total += day07_update_sum(g, child_idx);
        }
        g[idx].sum = total;
        return total;
    }
}

// Recursively find the unbalanced node
int day07_find_fault(vector<day07_node>& g, const size_t idx, const int diff=0, bool verbose=false) {
    if (g[idx].children.size() == 0) {
        return 0;
    } else {
        vector<int> sums;
        for (const size_t& child_idx : g[idx].children_idx) {
            sums.push_back(g[child_idx].sum);
        }
        int sfirst = sums[0];
        // Either sfirst differs from the others or one other is different
        size_t diffs = 0;
        for (size_t j=1; j<sums.size(); j++) {
            if (sums[j] != sfirst) {
                diffs++;
                if (verbose) {
                    cout << "Child '" << g[idx].children[j] << "' has different sum: " << sums[j] <<
                         " (expected: " << sfirst << ", diff: " << sfirst-sums[j] << ")\n";
                }
                // child j is the faulty, investigate
                day07_find_fault(g, g[idx].children_idx[j], sfirst-sums[j], verbose);
            }
        }
        if (diffs == 0) {
            if (verbose) {
                cout << "All children of '" << g[idx].name << "' are balanced, apply the diff here!\n";
                cout << "Change value from '" << g[idx].value << "' to '" << g[idx].value+diff << "'.\n";
            } else {
                cout << g[idx].value+diff << endl;
            }
        }
    }
}

void day07_a(string s, bool part_two, bool verbose) {
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
            vector<string> ch; ch.resize(0);
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
            n.has_parent = false;
            g.push_back(n);
        }
        //cout << "Added node: name: " << n.name << ", val: " << n.value << ", ch count: " << n.children.size() << endl;
    }
    if (verbose) cout << "Tree built!\n";
    // Set child indices and root flags
    for (size_t i=0; i<g.size(); i++) {
        if (g[i].children.size() > 0) {
            g[i].children_idx.resize(0);
            for (string child : g[i].children) {
                size_t j = day07_find_name(g, child);
                g[j].parent_idx = i;
                g[j].has_parent = true;
                g[i].children_idx.push_back(j);
            }
        }
    }
    // Find the nodes without parent
    string root_name;
    for (const day07_node& ni : g) {
        if (!ni.has_parent) {
            if (verbose) {
                cout << "'" << ni.name << "' doesn't have parent, it is the root node!\n";
            } else {
                cout << ni.name << endl;
            }
            root_name = ni.name;
        }
    }
    if (part_two) {
        size_t root_idx = day07_find_name(g, root_name);
        // Update sums
        size_t all_sum = day07_update_sum(g, root_idx);
        if (verbose) cout << "Fun fact: sum of whole graph is " << all_sum << ".\n";
        // Check balances
        size_t unbalanced_idx = 0;
        for (size_t i=0; i<g.size(); i++) {
            if (g[i].children.size() == 0) {
                // Terminal node balanced always
            } else {
                bool balanced = true;
                vector<int> sums;
                for (const size_t& child_idx : g[i].children_idx) {
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
                    if (verbose) cout << "Node '" << g[i].name << "' is not balanced! It's index is: '" << i << "'.\n";
                    unbalanced_idx = i;
                    break;
                }
            }
        }
        // Check who needs to be fixed
        day07_find_fault(g, unbalanced_idx);
    }
}

enum class day08_itype {
    inc,
    dec
};

enum class day08_ctype {
    equal,          /* == */
    greater,        /* >  */
    less,           /* <  */
    greater_or_eq,  /* >= */
    less_or_eq,     /* <= */
    not_equal       /* != */
};

struct day08_instruction {
    string reg;
    day08_itype inst_type;
    int val;
    string cond_reg;
    day08_ctype cond_type;
    int cond_val;

};

struct day08_reg {
    string name;
    int value;
};

bool day08_has_reg(const vector<day08_reg>& r, const string& name) {
    for (size_t i = 0; i < r.size(); i++) {
        if (r[i].name == name) return true;
    }
    return false;
}

size_t day08_find_reg(const vector<day08_reg>& r, const string& name) {
    for (size_t i=0; i<r.size(); i++) {
        if (r[i].name == name) return i;
    }
    cout << "ERROR: Cannot find register '" << name << "'\n";
    return 0;
}

int day08_read_reg(const vector<day08_reg>& r, const string& name) {
    size_t idx = day08_find_reg(r, name);
    return r[idx].value;
}

void day08_write_reg(vector<day08_reg>& r, const string& name, int new_value) {
    size_t idx = day08_find_reg(r, name);
    r[idx].value = new_value;
}

void day08_operate_reg(vector<day08_reg>& r, const string& name, day08_itype i, int val) {
    // Get current value
    int curr_val = day08_read_reg(r, name);
    int new_val;
    switch (i) {
        case day08_itype::inc:
            new_val = curr_val + val;
            break;
        case day08_itype::dec:
            new_val = curr_val - val;
            break;
    }
    day08_write_reg(r, name, new_val);
}

void day08_operate_reg(vector<day08_reg>& r, const day08_instruction& i) {
    day08_operate_reg(r, i.reg, i.inst_type, i.val);
}

bool day08_check_condition(day08_instruction i, const vector<day08_reg>& r) {
    string cond_reg_name = i.cond_reg;
    int cond_reg_val = day08_read_reg(r, cond_reg_name);
    int cond_right_hand_side = i.cond_val;
    switch (i.cond_type) {
        case day08_ctype::equal:
            return (cond_reg_val == cond_right_hand_side);
        case day08_ctype::not_equal:
            return (cond_reg_val != cond_right_hand_side);
        case day08_ctype::greater:
            return (cond_reg_val > cond_right_hand_side);
        case day08_ctype::greater_or_eq:
            return (cond_reg_val >= cond_right_hand_side);
        case day08_ctype::less:
            return (cond_reg_val < cond_right_hand_side);
        case day08_ctype::less_or_eq:
            return (cond_reg_val <= cond_right_hand_side);
    }
    cout << "ERROR: invalid condition type!\n";
    return false;
}

void day08_a(string s, bool part_two, bool verbose) {
    vector<string> instr = split(s, '\n');
    vector<string> parts;
    day08_instruction i;
    vector<day08_instruction> instructions;
    for (const string& istr : instr) {
        parts = split(istr, ' ');
        // Every instruction should consist of 7 parts
        // Example: t dec 614 if ewg <= -263
        if (parts.size() == 7) {
            i.reg = parts[0];
            if (parts[1] == "dec") {
                i.inst_type = day08_itype::dec;
            } else if (parts[1] == "inc") {
                i.inst_type = day08_itype::inc;
            } else {
                cout << "ERROR: Invalid instruction type (not inc or dec)\n";
            }
            i.val = stoi(parts[2]);
            if (!(parts[3] == "if")) {
                cout << "ERROR: Invalid instruction cond (not if)\n";
            }
            i.cond_reg = parts[4];
            string cond_str = parts[5];
            if (cond_str == "==") {
                i.cond_type = day08_ctype::equal;
            } else if (cond_str == "!=") {
                i.cond_type = day08_ctype::not_equal;
            } else if (cond_str == ">") {
                i.cond_type = day08_ctype::greater;
            } else if (cond_str == ">=") {
                i.cond_type = day08_ctype::greater_or_eq;
            } else if (cond_str == "<") {
                i.cond_type = day08_ctype::less;
            } else if (cond_str == "<=") {
                i.cond_type = day08_ctype::less_or_eq;
            } else {
                cout << "ERROR: Invalid instruction condition operator: " << cond_str << endl;
            }
            i.cond_val = stoi(parts[6]);
            instructions.push_back(i);
        } else {
            cout << "ERROR: Invalid instruction found in input file\n";
        }
    }
    if (verbose) cout << "Parsed " << instructions.size() << " instructions\n";

    // Initialize registers
    vector<day08_reg> registers;
    for (const day08_instruction& inst : instructions) {
        string iname1 = inst.reg;
        string iname2 = inst.cond_reg;
        day08_reg reg;
        reg.value = 0;
        if (!day08_has_reg(registers, iname1)) {
            // Initialize instruction register
            reg.name = iname1;
            registers.push_back(reg);
        }
        if (!day08_has_reg(registers, iname2)) {
            // Initialize condition register
            reg.name = iname2;
            registers.push_back(reg);
        }
    }
    if (verbose) cout << "Initialized " << registers.size() << " registers (0 value)\n";

    // Run the program
    int max_during_process = 0;
    for (const day08_instruction& inst : instructions) {
        if (day08_check_condition(inst, registers)) {
            day08_operate_reg(registers, inst);
        }
        if (part_two) {
            // Update max
            int max_val = 0;
            for (const day08_reg& r : registers) {
                if (r.value > max_val) max_val = r.value;
            }
            if (max_val > max_during_process) max_during_process = max_val;
        }
    }

    // Print registers
    int max = 0;
    string max_name;
    for (const day08_reg& r : registers) {
        //cout << r.name << "\t" << r.value << endl;
        if (r.value > max) {
            max = r.value;
            max_name = r.name;
        }
    }
    if (verbose) {
        cout << "Max value is '" << max << "' in '" << max_name << "'\n";
        cout << "Max value during the whole process is '" << max_during_process << "'\n";
    } else {
        cout << max << endl;
        cout << max_during_process << endl;
    }
}

size_t day09_a(string s, bool part_two) {
    vector<size_t> group_counts;
    group_counts.push_back(0);
    size_t depth = 0;
    bool garbage = false;
    bool skip = false;
    size_t garbage_chars = 0;
    for (const char c : s) {
        if (!skip) {
            switch (c) {
                case '{':
                    if (!garbage) {
                        // Descend and increment group counter
                        if (group_counts.size() - 1 < depth) { group_counts.push_back(0); }
                        group_counts[depth]++;
                        depth++;
                    } else {
                        garbage_chars++;
                    }
                    break;
                case '}':
                    if (!garbage) {
                        depth--;
                    } else {
                        garbage_chars++;
                    }
                    break;
                case '<':
                    if (!garbage) { garbage = true; }
                    else { garbage_chars++; }
                    break;
                case '!':
                    if (garbage) skip = true;
                    break;
                case '>':
                    if (!garbage) cout << "Warning: garbage end token before garbage open!\n";
                    garbage = false;
                    break;
                default:
                    if (garbage) garbage_chars++;
                    break;
            }
        } else {
            skip = false;
            // Skip this character
        }
    }
    size_t sum=0;
    for (size_t i=0; i<group_counts.size(); i++) {
        sum += (i+1)*group_counts[i];
    }
    if (!part_two) {
        return sum;
    } else {
        return garbage_chars;
    }
}

void day10_round(const vector<size_t>& lengths, size_t& current_position, size_t& skip_size, vector<size_t>& buffer) {
    for (const size_t& length : lengths) {
        size_t buffer_size = buffer.size();
        size_t idx_start = current_position;
        size_t idx_end = current_position + length;
        // Wrap around if needed
        if (idx_start >= buffer_size) { idx_start -= buffer_size; }
        if (idx_end >= buffer_size) { idx_end -= buffer_size; }
        // Reverse elements from idx_start to idx_end
        if (idx_start >= idx_end) {
            rotate(buffer.begin(), buffer.begin() + idx_start, buffer.end());
            reverse(buffer.begin(), buffer.begin() + length);
            rotate(buffer.begin(), buffer.begin() + buffer_size - idx_start, buffer.end());
        } else if (idx_start < idx_end) {
            reverse(buffer.begin() + idx_start, buffer.begin() + idx_end);
        }
        // Update current position
        current_position += length + skip_size;
        if (current_position >= buffer_size) { current_position = current_position % buffer_size; }
        skip_size++;
        if (skip_size >= buffer_size) { skip_size = skip_size % buffer_size; }
    }
}


size_t day10_a(string s, const size_t buffer_size) {
    // Split string around ','
    vector<string> lengths_str = split(s, ',');
    vector<size_t> lengths;
    for (const string& str : lengths_str) lengths.push_back(stoul(str));
    // Initialize circular list
    vector<size_t> buffer;
    for (size_t i=0; i<buffer_size; i++) buffer.push_back(i);
    // Initialize operation
    size_t current_position = 0;
    size_t skip_size = 0;
    day10_round(lengths, current_position, skip_size, buffer);
    return buffer[0]*buffer[1];
}

string day10_b(string s) {
    vector<size_t> lengths;
    for (const char c : s) {
        lengths.push_back((size_t)(c));
    }
    // Add standard length sequence
    lengths.push_back(17);
    lengths.push_back(31);
    lengths.push_back(73);
    lengths.push_back(47);
    lengths.push_back(23);
    // Initialize buffer
    vector<size_t> buffer;
    const size_t buffer_size = 256; const size_t rounds = 64;
    for (size_t i=0; i<buffer_size; i++) buffer.push_back(i);
    size_t current_position = 0;
    size_t skip_size = 0;
    // Run 64 passes
    for (size_t r=0; r<rounds; r++) {
        //cout << "Pass " << r << ", pos: " << current_position << ", skip: " << skip_size << endl;
        day10_round(lengths, current_position, skip_size, buffer);
    }
    // Calculate dense hash
    const size_t len = 16;
    vector<uint8_t> dense_hash;
    for (size_t j=0; j<buffer_size; j+=len) {
        uint8_t val = (uint8_t )buffer[j];
        for (size_t k=j+1; k<j+len; k++) {
            val ^= (uint8_t )buffer[k];
        }
        dense_hash.push_back(val);
    }
    if (dense_hash.size() != 16) { cout << "Error: incorrect dense hash size!\n"; }
    // Convert to hex representation
    return bytes_to_hex_string(dense_hash);
}

string knot_hash(const string s) {
    return day10_b(s);
}

template <class T>
size_t find_idx(const vector<T> &c, const T& e) {
    size_t i;
    for (i=0; i<c.size(); i++) {
        if (c[i] == e) return i;
    }
    return i;
}

size_t day11_get_steps(vector<size_t> counts) {
    // Counts show steps in order: N, NE, SE, S, SW, NW
    // N - S
    if (counts[0] > counts[3]) {
        counts[0]-=counts[3];
        counts[3]=0;
    } else {
        counts[3]-=counts[0];
        counts[0]=0;
    }
    // NE - SW
    if (counts[1] > counts[4]) {
        counts[1]-=counts[4];
        counts[4]=0;
    } else {
        counts[4]-=counts[1];
        counts[1]=0;
    }
    // SE - NW
    if (counts[2] > counts[5]) {
        counts[2]-=counts[5];
        counts[5]=0;
    } else {
        counts[5]-=counts[2];
        counts[2]=0;
    }
    // Combine
    size_t sum = 0;
    size_t min = counts[max_idx(counts)];
    for (size_t s : counts) {
        sum += s;
        if ((s != 0) && (s < min)) {
            min = s;
        }
    }
    return sum-min;
}

size_t day11_a(string s, bool part_two) {
    vector<string> directions = split(s, ',');
    vector<size_t> counts(6); // N, NE, SE, S, SW, NW
    for (size_t i=0; i<6; i++) counts[i]=0;
    vector<string> dir;
    dir.emplace_back("n");
    dir.emplace_back("ne");
    dir.emplace_back("se");
    dir.emplace_back("s");
    dir.emplace_back("sw");
    dir.emplace_back("nw");
    size_t max_length = 0;
    size_t curr_length = 0;
    for (const string & d : directions) {
        counts[find_idx(dir,d)]++;
        if (part_two) {
            curr_length = day11_get_steps(counts);
            if (max_length < curr_length) { max_length = curr_length; }
        }
    }
    if (!part_two) {
        return day11_get_steps(counts);
    } else {
        return max_length;
    }
}

struct vertex {
    size_t id;
    vector<size_t> edges;
    bool visited;
};

vector<size_t> day12_get_group(vector<vertex> &g, const size_t root_id) {
    // DFS
    vector<size_t> targets;
    vector<size_t> group;
    targets.push_back(root_id);
    vector<size_t> new_targets;
    bool dfs = true;
    while (dfs) {
        new_targets.resize(0);
        for (size_t id : targets) {
            g[id].visited = true;
            group.push_back(id);
            for (size_t e : g[id].edges) {
                if (! g[e].visited) {
                    new_targets.push_back(e);
                }
            }
        }
        if (new_targets.empty()) dfs = false;
        targets = new_targets;
    }
    return group;
}

size_t day12_count_graph_size(vector<vertex> &g, const size_t root_id) {
    return day12_get_group(g, root_id).size();
}

size_t day12_a(string input, bool part_two) {
    vector<string> vertex_strings = split(input, '\n');
    vector<string> parts;
    vertex v;
    v.visited = false;
    vector<vertex> g;
    for (const string& s : vertex_strings) {
        // self <=> x, y, z
        parts = split(s, '>');
        v.id = stoul(parts[0].substr(0, parts[0].size()-3));
        v.edges.resize(0);
        for (const string& e : split(parts[1],',')) {
            v.edges.push_back(stoul(e));
        }
        g.push_back(v);
        //cout << "Added vertex '" << v.id << "' with edges to: ";
        //for (size_t e : v.edges) cout << e << " ";
        //cout << endl;
    }
    // Traverse graph starting from id 0
    if (!part_two) {
        return day12_count_graph_size(g, 0);
    } else {
        bool exploring = true;
        size_t starting_vertex = 0;
        size_t groups = 0;
        while (exploring) {
            vector<size_t> group = day12_get_group(g, starting_vertex);
            groups++;
            //cout << "Group connected to '" << starting_vertex << "' with size: " << group.size() << endl;
            // Select next index from g which is unexplored, also terminate if no unvisited vertex found
            exploring = false;
            for (size_t i=0; i<g.size(); i++) {
                if (!g[i].visited) {
                    starting_vertex = i; exploring = true;
                }
            }
        }
        return groups;
    }
    return 0;
}



size_t day13_a(string s, bool part_two) {
    vector<size_t> depth, range;
    for (const string& line : split(s, '\n')) {
        vector<string> parts = split(line, ':');
        depth.push_back(stoul(parts[0]));
        range.push_back(stoul(parts[1]));
    }
    //cout << "Firewall has " << depth.size() << " layers\n";
    // Calculate which scanner catches our packet
    /**
     * The time(s) for layer L at depth D with range R, where the scanner
     * is at the top is
     *  t_top = 2*(R-1)*k,
     * That is for a layer with R=5, the scanner is at the top at
     *  t_top = 0,8,16,24 etc
     * Because our packet starts at D=0 and descends 1 depth at each time step,
     * to check if its caught at layer L
     *  caught = D == 2*(R-1)*k
     *  that is D%(2*R-2)==0
     */
    size_t caught=0;
    size_t severity=0;
    for (size_t i=0; i<depth.size(); i++) {
        if (depth[i] % (2*range[i]-2) == 0) {
            caught++;
            severity += depth[i]*range[i];
        }
    }
    //cout << "Packet caught in " << caught << " layers!\n";
    if (!part_two) {
        return severity;
    } else {
        cout << "Severity: " << severity << endl;
    }
    // Part two: now add a delay so that our packet won't get caught at all
    /**
     * This time our packet starts at D=0 at T0 and descends 1 depth at each time step,
     * to check if its caught at layer L
     *  t_top = 2*(R-1)*k, depth: d=D
     * packet is at depth:
     *  d_packet = t+t0
     *  that is (d+T0)%(2*R-2)==0
     */
    // Brute force solution
    size_t t0 = 0;
    while (true) {
        t0++;
        bool pass = true;
        for (size_t i=0; i<depth.size(); i++) {
            if ((t0+depth[i]) % (2*range[i]-2) == 0) {
                pass = false;
                break;
            }
        }
        if (pass) break;
    }
    cout << "Lowest delay: " << t0 << endl;
    // Elegant solution
    // TODO: Inverse Chinese Remainder Theorem
    return t0;
}

struct day14_node {
    pair<int,int> coord;
    bool occupied;
    bool visited;
    size_t group;
};

vector<pair<int,int>> day14_get_neighbours(const pair<int,int> coord) {
    int i = coord.first;
    int j = coord.second;
    vector<pair<int,int>> n;
    if (i>0)    n.emplace_back(pair<int,int>(i-1,j));
    if (i<127)  n.emplace_back(pair<int,int>(i+1,j));
    if (j>0)    n.emplace_back(pair<int,int>(i,j-1));
    if (j<127)  n.emplace_back(pair<int,int>(i,j+1));
    return n;
};

size_t day14_find_next_occupied(const vector<day14_node>& g) {
    for (size_t i=0; i<g.size(); i++) {
        if ((g[i].occupied) && !(g[i].visited)) return i;
    }
    return g.size();
}

void day14_generate_bitmap(vector<day14_node>& g, size_t groups) {
    const size_t tile_size = 4;
    vector<size_t> group_counts;
    group_counts.resize(groups);
    fill(group_counts.begin(),group_counts.end(),0);
    for (day14_node n : g) {
        if (n.occupied) {
            group_counts[n.group]++;
        }
    }
    vector<size_t> colours;
    colours.resize(groups);
    for (size_t i=0; i<groups; i++) {
        if (group_counts[i]==1) {
            colours[i]=colourPalette[0];
        } else {
            colours[i]=colourPalette[i%63+1];
        }
    }
    // Fill image with white
    bitmap_image img(tile_size*128,tile_size*128);
    img.set_all_channels(255,255,255);
    size_t occupied_count = 0;
    for (day14_node n : g) {
        uint8_t red=255,green=255,blue=255;
        if (n.occupied) {
            occupied_count++;
            size_t colour = colours[n.group];
            red =   uint8_t(colour >> 16);
            green = uint8_t(colour >> 8);
            blue =  uint8_t(colour);
        }
        for (size_t tx = 0; tx < tile_size; tx++) {
            for (size_t ty = 0; ty < tile_size; ty++) {
                img.set_pixel(tile_size*n.coord.first+tx, tile_size*n.coord.second+ty, red, green, blue);
            }
        }
    }
    cout << "Occupied " << occupied_count << " of " << 128*128 << " (" << double(occupied_count)/163.84 << "%)\n";
    img.save_image("day14.bmp");
    // Now generate the de-fragmented version
    vector<pair<size_t,size_t>> group_count_colour;
    for (size_t i=0; i<groups; i++) {
        group_count_colour.push_back(pair<size_t,size_t>(group_counts[i], colours[i]));
    }
    sort(group_count_colour.begin(), group_count_colour.end(), [](pair<size_t,size_t> a, pair<size_t,size_t> b) {
        return a.first > b.first;
    });
    size_t pix = 0;
    bitmap_image img_defrag(tile_size*128,tile_size*128);
    img_defrag.set_all_channels(255,255,255);
    for (pair<size_t,size_t> gc : group_count_colour) {
        //cout << "Group size: " << gc.first << endl;
        uint8_t red, green, blue;
        size_t colour = gc.second;
        red =   uint8_t(colour >> 16);
        green = uint8_t(colour >> 8);
        blue =  uint8_t(colour);
        // Set the next group to the same colour
        for (size_t i=pix; i<pix+gc.first; i++) {
            size_t col = i/128;
            size_t row = i%128;
            for (size_t tx = 0; tx < tile_size; tx++) {
                for (size_t ty = 0; ty < tile_size; ty++) {
                    img_defrag.set_pixel(tile_size*row+tx, tile_size*col+ty, red, green, blue);
                }
            }
        }
        pix += gc.first;
    }
    img_defrag.save_image("day14_defrag.bmp");
}

void day14_mark_group(vector<day14_node>& g, size_t start_idx, size_t group_tag=0) {
    g[start_idx].visited = true;
    g[start_idx].group = group_tag;
    vector<pair<int,int>> n = day14_get_neighbours(g[start_idx].coord);
    for (const pair<int,int>& c : n) {
        size_t i = (size_t)(c.first*128+c.second);
        if (i >= g.size()) {
            cout << "ERROR!\n";
        }
        if ((g[i].occupied) && !(g[i].visited)) {
            day14_mark_group(g, i, group_tag);
        }
    }
}

size_t day14_a(string s, bool part_two, bool generate_bitmap) {
    vector<string> hashes, bin_hashes;
    hashes.resize(128);
    bin_hashes.resize(128);
    for (size_t i=0; i<128; i++) {
        string hash_input = s + "-" + to_string(i);
        hashes[i] = knot_hash(hash_input);
        bin_hashes[i] = hex_string_to_binary(hashes[i]);
    }
    vector<vector<bool>> grid;
    vector<bool> row;
    size_t count=0;
    for (const string &bin_hash : bin_hashes) {
        row.resize(0);
        for (char c : bin_hash) {
            if (c == '1') {
                row.push_back(true);
                count++;
            } else {
                row.push_back(false);
            }
        }
        if (row.size() == 128) {
            grid.push_back(row);
        } else {
            cout << "Error in hashes!\n";
        }
    }
    if (!part_two) return count;
    // We need to traverse the grid and mark all occupied blocks visited
    vector<day14_node> g;
    day14_node n;
    n.visited = false;
    for (size_t i=0; i<128; i++) {
        for (size_t j=0; j<128; j++) {
            n.coord = pair<int,int>(i, j);
            n.occupied = grid[i][j];
            g.push_back(n);
        }
    }
    size_t groups = 0;
    while (true) {
        size_t target = day14_find_next_occupied(g);
        //cout << "Target: " << target << endl;
        if (target == g.size()) {
            // Finished, no more unmarked group
            break;
        }
        day14_mark_group(g, target, groups);
        groups++;
    }
    if (generate_bitmap) {
        day14_generate_bitmap(g, groups);
    }
    return groups;
}

size_t day15_a(string s, bool part_two){
    vector<string> lines = split(s, '\n');
    const size_t start_A = stoul(split(lines[0], ' ').back());
    const size_t start_B = stoul(split(lines[1], ' ').back());
    //cout << "Starting values for generators " << start_A << ", " << start_B << endl;
    const size_t factor_A = 16807;
    const size_t factor_B = 48271;
    const size_t div = 2147483647;
    const size_t samples = 40000000;
    size_t match=0;
    size_t val_A=start_A, val_B=start_B;
    if (!part_two) {
        for (size_t i = 0; i < samples; i++) {
            val_A = (val_A * factor_A) % div; // Update A
            val_B = (val_B * factor_B) % div; // Update B
            if ((uint16_t) val_A == (uint16_t) val_B) match++;  // Compare
        }
        return match;
    }
    // Reset generators
    val_A=start_A, val_B=start_B;
    match=0;
    const size_t div_A = 4;
    const size_t div_B = 8;
    const size_t samples_b = 5000000;
    for (size_t i=0; i<samples_b; i++) {
        do { val_A = (val_A*factor_A)%div; } while (val_A % div_A != 0);
        do { val_B = (val_B*factor_B)%div; } while (val_B % div_B != 0);
        if ((uint16_t)val_A == (uint16_t)val_B) match++;  // Compare
    }
    return match;
}

enum class day16_move_type {
    spin,
    exchange,
    partner
};

struct day16_move {
    day16_move_type t;
    char A, B;
};

void day16_dance(const vector<day16_move>& moves, vector<char>& dancers) {
    size_t loc_A, loc_B;
    for (const day16_move &move : moves) {
        switch (move.t) {
            case day16_move_type::spin:
                // Rotate dancers with amount
                rotate(dancers.begin(), dancers.begin() + 16 - (move.A) % 16, dancers.end());
                break;
            case day16_move_type::exchange:
                // Exchange programs at loc A and B
                swap(dancers[move.A], dancers[move.B]);
                break;
            case day16_move_type::partner:
                // Exchange programs named A and B
                loc_A = (size_t) find(dancers, move.A);
                loc_B = (size_t) find(dancers, move.B);
                swap(dancers[loc_A], dancers[loc_B]);
                break;
        }
    }
}

string day16_a(string s, bool part_two) {
    vector<string> moves_str = split(s,',');
    vector<string> parts;
    vector<day16_move> moves;
    for (string move : moves_str) {
        char type = move[0];
        day16_move m;
        switch (type) {
            case 's': // sX, example s18
                m.t = day16_move_type::spin;
                m.A = (char)stoul(move.substr(1));
                m.B = 0;
                break;
            case 'x':
                m.t = day16_move_type::exchange;
                parts = split(move.substr(1), '/');
                m.A = (char)stoul(parts[0]);
                m.B = (char)stoul(parts[1]);
                break;
            case 'p':
                m.t = day16_move_type::partner;
                parts = split(move.substr(1), '/');
                m.A = parts[0][0];
                m.B = parts[1][0];
                break;
            default:
                break;
        }
        moves.push_back(m);
    }
    // Initialize dancers
    vector<char> dancers;
    char c = 'a';
    for (size_t i=0; i<16; i++) dancers.push_back(c++);
    // Start the dance
    bool period_found = false;
    size_t period;
    size_t dance_count=0;
    size_t dances=0;
    while (!period_found) {
        dances++;
        // Do a dance
        day16_dance(moves, dancers);
        bool equal = true;
        for (size_t i=0; i<16; i++) {
            if (dancers[i] != 'a'+i) {
                equal = false;
                break;
            }
        }
        if (equal) {
            period = dances;
            period_found = true;
            dance_count = 1000000000%period;
            cout << "Period: " << period << ", dances to do: " << dance_count << endl;
        }
        // Escape loop for part one
        if (!part_two) period_found = true;
    }
    string result;
    if (!part_two) {
        result = "";
        for (char p : dancers) result+=p;
        return result;
    }
    // Dance further
    for (size_t i=0; i<dance_count; i++) {
        day16_dance(moves, dancers);
    }
    result = "";
    for (char p : dancers) result+=p;
    return result;
}

size_t day17_a(const size_t s, bool part_two) {
    if (!part_two) {
        CircularBuffer<size_t> b(0);
        size_t idx = 0;
        for (size_t i=1; i<=2017; i++) {
            //b.insert_behind(i-1,i,s);
            idx = b.insert_behind_idx(idx, i, s);
        }
        return b.get(b.find(2017).next).value;
    } else {
        // This takes around 9 minutes
        /*CircularBuffer<size_t> b(0, 50000010);
        size_t idx = 0;
        for (size_t i=1; i<=50000000; i++) {
            idx = b.insert_behind_idx(idx,i,s);
        }
        return b.get(b.find(0).next).value;*/
        // Do the math instead
        size_t p = 0;
        size_t next_of_zero = 0;
        for (size_t i=0; i<=50000000; i++) {
            if (p == 0) next_of_zero = i;
            p = (p+1+s%(i+1))%(i+1);
        }
        return next_of_zero;
    }
}

enum class day18_type {
    snd,
    set,
    add,
    mul,
    mod,
    rcv,
    jgz
};

enum class day18_arg_type {
    reg,
    val
};

struct day18_instruction {
    day18_type type;
    day18_arg_type type_a;
    long long int reg_a;
    day18_arg_type type_b;
    long long int reg_b;
};

class day18_program {
private:
    vector<day18_instruction> program;
    vector<char> reg_names;
    vector<long long int> reg_vals;
    size_t iptr;
public:
    list<long long int> out;
    long long int input;
    bool terminated;
    bool waiting;
    day18_program(const string s, const long long int pid=0) {
        terminated = false;
        waiting = false;
        vector<string> parts;
        reg_names.resize(0);
        out.resize(0);
        // First gather register names
        for (const string& line : split(s,'\n')) {
            parts = split(line, ' ');
            char regname = parts[1][0];
            try {
                stoi(parts[1]);
            } catch (...) {
                if (find(reg_names, regname) >= reg_names.size()) {
                    reg_names.push_back(regname);
                }
            }
        }
        //cout << "Registers: " << reg_names.size() << endl;
        //for (char r : reg_names) cout << r << " ";
        //cout << endl;
        // Now parse instructions
        day18_instruction i;
        for (const string& line : split(s,'\n')) {
            parts = split(line, ' ');
            string itype = parts[0];
            int reg_a, reg_b;
            day18_arg_type type_a, type_b;
            try {
                reg_a = stoi(parts[1]);
                type_a = day18_arg_type::val;
            } catch (...) {
                reg_a = (int)parts[1][0];
                type_a = day18_arg_type::reg;
            }
            if (parts.size() > 2) {
                try {
                    reg_b = stoi(parts[2]);
                    type_b = day18_arg_type::val;
                } catch (...) {
                    reg_b = (int)parts[2][0];
                    type_b = day18_arg_type::reg;
                }
            }
            if        (itype == "snd") {
                i.type = day18_type::snd;
                i.reg_a = reg_a; i.type_a = type_a;
            } else if (itype == "rcv") {
                i.type = day18_type::rcv;
                i.reg_a = reg_a; i.type_a = type_a;
            } else if (itype == "set") {
                i.type = day18_type::set;
                i.reg_a = reg_a; i.type_a = type_a;
                i.reg_b = reg_b; i.type_b = type_b;
            } else if (itype == "add") {
                i.type = day18_type::add;
                i.reg_a = reg_a; i.type_a = type_a;
                i.reg_b = reg_b; i.type_b = type_b;
            } else if (itype == "mul") {
                i.type = day18_type::mul;
                i.reg_a = reg_a; i.type_a = type_a;
                i.reg_b = reg_b; i.type_b = type_b;
            } else if (itype == "mod") {
                i.type = day18_type::mod;
                i.reg_a = reg_a; i.type_a = type_a;
                i.reg_b = reg_b; i.type_b = type_b;
            }  else if (itype == "jgz") {
                i.type = day18_type::jgz;
                i.reg_a = reg_a; i.type_a = type_a;
                i.reg_b = reg_b; i.type_b = type_b;
            }
            program.push_back(i);
        }
        // Initialize reg vals
        for (char c : reg_names) reg_vals.push_back(0);
        // Set value of reg p to pid
        reg_vals[find(reg_names,'p')]=pid;
        // Set iptr to 0
        iptr = 0;
    }
    void run(bool part_two = false, bool received = false) {
        bool running = true;
        waiting = false;
        long long int sent;
        // Run the program
        while (running) {
            day18_instruction i = program[iptr];
            //for (int v : reg_vals) cout << v << " ";
            //cout << endl;
            switch (i.type) {
                case day18_type::snd:
                    if (i.type_a == day18_arg_type::val) { sent = i.reg_a; }
                    else { sent = reg_vals[find(reg_names, (char)i.reg_a)]; }
                    out.push_back(sent);
                    iptr++;
                    break;
                case day18_type::rcv:
                    if (!part_two) {
                        if (i.type_a == day18_arg_type::val) {
                            if (i.reg_a != 0) waiting = true;
                        }
                        else {
                            if (reg_vals[find(reg_names, (char)i.reg_a)] != 0) waiting = true;
                        }
                        iptr++;
                    } else {
                        // Part two: wait always for the incoming value
                        if (received) {
                            // Store the received value
                            reg_vals[find(reg_names, (char)i.reg_a)] = input;
                            // Clear received flag
                            received = false;
                            iptr++;
                        } else {
                            waiting = true;
                        }
                    }
                    break;
                case day18_type::set:
                    if (i.type_b == day18_arg_type::reg) {
                        reg_vals[find(reg_names, (char)i.reg_a)] = reg_vals[find(reg_names, (char)i.reg_b)];
                    } else {
                        reg_vals[find(reg_names, (char)i.reg_a)] = i.reg_b;
                    }
                    iptr++;
                    break;
                case day18_type::add:
                    if (i.type_b == day18_arg_type::reg) {
                        reg_vals[find(reg_names, (char)i.reg_a)] += reg_vals[find(reg_names, (char)i.reg_b)];
                    } else {
                        reg_vals[find(reg_names, (char)i.reg_a)] += i.reg_b;
                    }
                    iptr++;
                    break;
                case day18_type::mul:
                    if (i.type_b == day18_arg_type::reg) {
                        reg_vals[find(reg_names, (char)i.reg_a)] *= reg_vals[find(reg_names, (char)i.reg_b)];
                    } else {
                        reg_vals[find(reg_names, (char)i.reg_a)] *= i.reg_b;
                    }
                    iptr++;
                    break;
                case day18_type::mod:
                    if (i.type_b == day18_arg_type::reg) {
                        reg_vals[find(reg_names, (char)i.reg_a)] = reg_vals[find(reg_names, (char)i.reg_a)] %
                                                                   reg_vals[find(reg_names, (char)i.reg_b)];
                    } else {
                        reg_vals[find(reg_names, (char)i.reg_a)] = reg_vals[find(reg_names, (char)i.reg_a)] % i.reg_b;
                    }
                    iptr++;
                    break;
                case day18_type::jgz:
                {
                    bool jump;
                    if (i.type_a == day18_arg_type::val) {
                        jump = (i.reg_a > 0);
                    } else {
                        jump = (reg_vals[find(reg_names, (char)i.reg_a)] > 0);
                    }
                    if (jump) {
                        if (i.type_b == day18_arg_type::val) {
                            iptr += i.reg_b;
                        } else {
                            iptr += reg_vals[find(reg_names, (char)i.reg_b)];
                        }
                    } else {
                        iptr++;
                    }
                }
                    break;
            }
            if ((iptr < 0) || (iptr >= program.size())) {
                running = false;
                terminated = true;
            }
            if (waiting) {
                running = false;
            }
        }
        return;
    }
};

long long int day18_a(string s, bool part_two) {
    if (!part_two) {
        day18_program p(s);
        p.run();
        return p.out.back();
    } else {
        day18_program p0(s,0);
        day18_program p1(s,1);
        p0.run(part_two);
        p1.run(part_two);
        size_t p1_sent_value_to_p0 = 0;
        while (true) {
            if (!p0.terminated) {
                if(!p1.out.empty()) {
                    p0.input = p1.out.front();
                    p1.out.pop_front();
                    //cout << "Running p0 with input from p1: " << p0.input << endl;
                    p0.run(part_two, true);
                    p1_sent_value_to_p0++;
                } else {
                    // Both queues are empty
                    if(p0.out.empty()) break;
                    //cout << "p0 is waiting for input from p1\n";
                }
            } else {
                // p0 wont send more to p1, p1 cannot continue
                if(p0.out.empty()) break;
            }
            if (!p1.terminated) {
                if(!p0.out.empty()) {
                    p1.input = p0.out.front();
                    p0.out.pop_front();
                    //cout << "Running p1 with input from p0: " << p1.input << endl;
                    p1.run(part_two, true);

                } else {
                    // Both queues are empty
                    if(p1.out.empty()) break;
                    //cout << "p0 is waiting for input from p1\n";
                }
            } else {
                // p1 wont send more to p0, p0 cannot continue
                if(p1.out.empty()) break;
            }
        }
        return p1_sent_value_to_p0;
    }
    return 0;
}

enum class day19_dir {
    up, down, left, right
};

const day19_dir directions[] = {day19_dir::up, day19_dir::down, day19_dir::left, day19_dir::right};

pair<size_t,size_t> day19_step(pair<size_t,size_t> next, const day19_dir d) {
    switch (d) {
        case day19_dir::down:
            next.first++;
            break;
        case day19_dir::up:
            next.first--;
            break;
        case day19_dir::left:
            next.second--;
            break;
        case day19_dir::right:
            next.second++;
            break;
    }
    return next;
};

string day19_dir_label(const day19_dir d) {
    switch (d) {
        case day19_dir::down:
            return "down";
        case day19_dir::up:
            return "up";
        case day19_dir::left:
            return "left";
        case day19_dir::right:
            return "right";
    }
}

day19_dir day19_opposite(const day19_dir d) {
    switch (d) {
        case day19_dir::down:
            return day19_dir::up;
        case day19_dir::up:
            return day19_dir::down;
        case day19_dir::left:
            return day19_dir::right;
        case day19_dir::right:
            return day19_dir::left;
    }
};

bool day19_get(const vector<vector<char>> &map, pair<size_t,size_t> pos, char& c) {
    size_t rows = map.size();
    size_t cols = map[0].size();
    if (pos.first >= rows || pos.second >= cols) return false;
    c = map[pos.first][pos.second];
    return true;
}

string day19_a(string s, bool part_two, bool print_animation) {
    vector<vector<char>> map;
    size_t rows, cols;
    for (string &line : split(s,'\n')) {
        vector<char> row;
        for (char &c : line) row.push_back(c);
        map.push_back(row);
    }
    rows = map.size();
    cols = map[0].size();
    // Find start
    pair<size_t, size_t> pos;
    pos.first = 0;
    for (size_t j=0; j<cols; j++) {
        if (map[0][j] == '|') pos.second = j;
    }
    day19_dir d = day19_dir::down;
    pair<size_t, size_t> next_pos;
    string letters = "";
    char c;
    bool wandering = true;
    size_t steps = 1;
    bitmap_image img(cols,rows);
    if (print_animation) {
        img.set_all_channels(255,255,255);
        for (size_t i=0; i<rows; i++) {
            for (size_t j=0; j<cols; j++) {
                if (map[i][j] != ' ') {
                    img.set_pixel(j, i, 0, 0, 0);
                }
            }
        }
        img.set_pixel(pos.second, pos.first, 0, 200, 255);
        img.save_image("frame_"+to_string(steps)+".bmp");
    }
    while (wandering) { // Wandering in the tube network
        next_pos = day19_step(pos, d);
        img.set_pixel(pos.second, pos.first, 255, 0, 0);
        // Check if we've left the map
        if (!day19_get(map, next_pos, c)) wandering = false;
        // Examine next char
        switch (c) {
            case '|':
            case '-':
                // Continue with the same direction
                pos = next_pos; steps++;
                break;
            case '+': {   // Turn towards a valid cell
                vector<day19_dir> neighbours;
                day19_dir d_old = d;
                switch (d) {
                    case day19_dir::up:
                    case day19_dir::down:
                        neighbours.push_back(day19_dir::left);
                        neighbours.push_back(day19_dir::right);
                        break;
                    case day19_dir::left:
                    case day19_dir::right:
                        neighbours.push_back(day19_dir::up);
                        neighbours.push_back(day19_dir::down);
                        break;
                }
                for (day19_dir d_new : neighbours) {
                    char c_n;
                    if (day19_get(map, day19_step(next_pos, d_new), c_n)) {
                        switch (c_n) {
                            case ' ':
                                // Not valid, go on
                                break;
                            case '|':
                                if (d_new == day19_dir::up || d_new == day19_dir::down) d = d_new;
                                break;
                            case '-':
                                if (d_new == day19_dir::left || d_new == day19_dir::right) d = d_new;
                                break;
                            default:
                                // Letter is also valid, go on
                                letters += c_n;
                                d = d_new;
                                break;
                        }
                    }
                }
                // If we didn't find new direction, end the wandering
                if (d_old == d) {
                    wandering = false;
                } else {
                    pos = next_pos; steps++;
                }
            }
                break;
            case ' ':
                // Shouldn't happen, only at termination
                wandering = false;
                break;
            default:
                // This is a letter, save it and continue
                letters+=c;
                pos = next_pos; steps++;
                break;
        } // end switch(c)
        if (print_animation) {
            img.set_pixel(pos.second, pos.first, 0, 200, 255);
            img.save_image("frame_"+to_string(steps)+".bmp");
        }
    } // end while
    if (!part_two) {
        return letters;
    } else {
        return to_string(steps);
    }

}

struct vec3i {
    int x, y, z;
};

vec3i string_to_vec3i(const string s, const char delim=',') {
    vector<string> parts = split(s, delim);
    return {stoi(parts[0]), stoi(parts[1]), stoi(parts[2])};
}

int vec3i_norm0(const vec3i& v) {
    return abs(v.x)+abs(v.y)+abs(v.z);
}

bool vec3i_equal(const vec3i& l, const vec3i& r) {
    return (l.x == r.x) && (l.y == r.y) && (l.z == r.z);
}

vec3i vec3i_add(const vec3i& l, const vec3i& r) {
    return {l.x+r.x, l.y+r.y, l.z+r.z};
}

class day20_particle {
public:
    vec3i pos, vel, acc;
    day20_particle(const vec3i &pos, const vec3i &vel, const vec3i &acc) : pos(pos), vel(vel), acc(acc) {}
    void update() {
        vel = vec3i_add(vel, acc);
        pos = vec3i_add(pos, vel);
    }
};

size_t day20_a(string s, bool part_two) {
    vector<string> parts;
    vec3i pos, vel, acc;
    vector<day20_particle> particles;
    for (string line : split(s, '\n')) {
        // Every line has a format of
        // p=<-11104,1791,5208>, v=<-6,36,-84>, a=<19,-5,-4>
        parts = split(line, '<');
        if (parts.size() == 4) {
            pos = string_to_vec3i(split(parts[1], '>')[0]);
            vel = string_to_vec3i(split(parts[2], '>')[0]);
            acc = string_to_vec3i(split(parts[3], '>')[0]);
            particles.push_back(day20_particle(pos, vel, acc));
        }
    }
    //cout << "Particles: " << particles.size() << endl;
    if (!part_two) {
        // Find the one with the lowest norm0 of acceleration
        int min_acc = 99999;
        size_t p_idx = 0;
        for (size_t i=0; i<particles.size(); i++) {
            int n = vec3i_norm0(particles[i].acc);
            if (n < min_acc) {
                min_acc = n; p_idx = i;
            }
        }
        return p_idx;
    }
    // Part two
    bool resolving_collisions = true;
    vector<size_t> to_erase;
    size_t steps = 0;
    while (resolving_collisions) {
        // Find collisions
        to_erase.resize(0);
        for (size_t i=0; i<particles.size()-1; i++) {
            for (size_t j=i+1; j<particles.size(); j++) {
                if (vec3i_equal(particles[i].pos, particles[j].pos)) {
                    if (find(to_erase, i) >= to_erase.size()) to_erase.push_back(i);
                    if (find(to_erase, j) >= to_erase.size()) to_erase.push_back(j);
                }
            }
        }
        // Erase them
        while (!to_erase.empty()) {
            particles.erase(particles.begin()+to_erase.back());
            to_erase.pop_back();
        }
        // Update particles
        for (day20_particle &p : particles) {
            p.update();
        }
        steps++;
        if (steps >= 1000) {
            resolving_collisions = false;
            cout << "steps: " << steps << " particles: " << particles.size() << endl;
        }
    }
    return particles.size();
}

#endif //TODAY_ONLY

bool day21_pix(const char c) {
    return (c=='#');
}

class day21_blk2 {
public:
    bool data[2][2];
    day21_blk2(const string& s) {
        data[0][0] = day21_pix(s[0]);
        data[0][1] = day21_pix(s[1]);
        data[1][0] = day21_pix(s[3]);
        data[1][1] = day21_pix(s[4]);
    }
    day21_blk2(bool a, bool b, bool c, bool d) : data{{a,b},{c,d}} {}
    day21_blk2 flip_h() { return day21_blk2(data[1][0],data[1][1],
                                            data[0][0],data[0][1]); }
    day21_blk2 flip_v() { return day21_blk2(data[0][1],data[0][0],
                                            data[1][1],data[1][0]); }
    day21_blk2 rotate() { return day21_blk2(data[0][1],data[1][1],
                                            data[0][0],data[1][0]); }
    bool equal_to(const day21_blk2& b) const {
        return data[0][0] == b.data[0][0] && data[0][1] == b.data[0][1] &&
               data[1][0] == b.data[1][0] && data[1][1] == b.data[1][1];
    }
};

class day21_blk3 {
public:
    bool data[3][3];
    day21_blk3(const string& s) {
        data[0][0] = day21_pix(s[0]);
        data[0][1] = day21_pix(s[1]);
        data[0][2] = day21_pix(s[2]);
        data[1][0] = day21_pix(s[4]);
        data[1][1] = day21_pix(s[5]);
        data[1][2] = day21_pix(s[6]);
        data[2][0] = day21_pix(s[8]);
        data[2][1] = day21_pix(s[9]);
        data[2][2] = day21_pix(s[10]);
    }
    day21_blk3(bool a, bool b, bool c,
                bool d, bool e, bool f,
                bool g, bool h, bool i) : data{{a,b,c},{d,e,f},{g,h,i}} {}
    day21_blk3 flip_h() { return day21_blk3(data[2][0],data[2][1],data[2][2],
                                            data[1][0],data[1][1],data[1][2],
                                            data[0][0],data[0][1],data[0][2]); }
    day21_blk3 flip_v() { return day21_blk3(data[0][2],data[0][1],data[0][0],
                                            data[1][2],data[1][1],data[1][0],
                                            data[2][2],data[2][1],data[2][0]); }
    day21_blk3 rotate() { return day21_blk3(data[0][2],data[1][2],data[2][2],
                                            data[0][1],data[1][1],data[2][1],
                                            data[0][0],data[1][0],data[2][0]); }
    bool equal_to(const day21_blk3& b) const {
        return data[0][0] == b.data[0][0] && data[0][1] == b.data[0][1] && data[0][2] == b.data[0][2] &&
               data[1][0] == b.data[1][0] && data[1][1] == b.data[1][1] && data[1][2] == b.data[1][2] &&
               data[2][0] == b.data[2][0] && data[2][1] == b.data[2][1] && data[2][2] == b.data[2][2];
    }
};

class day21_blk4 {
public:
    bool data[4][4];
    day21_blk4(const string& s) {
        data[0][0] = day21_pix(s[0]);
        data[0][1] = day21_pix(s[1]);
        data[0][2] = day21_pix(s[2]);
        data[0][3] = day21_pix(s[3]); // skip 4 '/'
        data[1][0] = day21_pix(s[5]);
        data[1][1] = day21_pix(s[6]);
        data[1][2] = day21_pix(s[7]);
        data[1][3] = day21_pix(s[8]); // skip 9 '/'
        data[2][0] = day21_pix(s[10]);
        data[2][1] = day21_pix(s[11]);
        data[2][2] = day21_pix(s[12]);
        data[2][3] = day21_pix(s[13]); // skip 14 '/'
        data[3][0] = day21_pix(s[15]);
        data[3][1] = day21_pix(s[16]);
        data[3][2] = day21_pix(s[17]);
        data[3][3] = day21_pix(s[18]);
    }
};

class day21_rule23 {
public:
    day21_blk2 input;
    day21_blk3 output;
    day21_rule23(const string &i, const string &o) : input(i), output(o) {}
};

class day21_rule34 {
public:
    day21_blk3 input;
    day21_blk4 output;
    day21_rule34(const string &i, const string &o) : input(i), output(o) {}
};

template <class blk_in, class blk_out, class rule_T>
blk_out replace(const vector<rule_T>& r, blk_in b) {
    // Generate the alternates of block b
    blk_in fh = b.flip_h();
    blk_in fv = b.flip_v();
    vector<blk_in> blocks;
    blocks.push_back(b);
    blocks.push_back(fh);
    blocks.push_back(fv);
    for (size_t i=0; i<3; i++) {
        b = b.rotate(); fh = fh.rotate(); fv = fv.rotate();
        blocks.push_back(b);
        blocks.push_back(fh);
        blocks.push_back(fv);
    }
    for (const rule_T& rule : r) {
        for (const blk_in blk : blocks) {
            if (blk.equal_to(rule.input)) {
                return rule.output;
            }
        }
    }
}

size_t day21_a(string s, bool part_two) {
    // Parse the rules
    vector<day21_rule23> r23;
    vector<day21_rule34> r34;
    for (const string& line : split(s,'\n')) {
        vector<string> parts = split(line, '/');
        if (parts.size() == 4) {
            parts = split(line, ' ');
            r23.emplace_back(day21_rule23(parts[0],parts[2]));
        } else if (parts.size() == 6) {
            parts = split(line, ' ');
            r34.emplace_back(day21_rule34(parts[0],parts[2]));
        }
    }
    vector<vector<bool>> image;
    const bool ON = true;
    const bool OFF = false;
    //.#.
    //..#
    //###
    image.push_back({ OFF, ON, OFF });
    image.push_back({ OFF, OFF, ON });
    image.push_back({ ON, ON, ON });
    size_t iterations = 0;
    if (!part_two) iterations = 5;
    else iterations = 18;
    for (size_t it=0; it<iterations; it++) {
        vector<vector<bool>> new_image;
        if (image.size() % 2 == 0) {
            // Create new canvas
            size_t new_size = image.size()/2*3;
            vector<bool> row(new_size);
            for (size_t nr = 0; nr<new_size; nr++) new_image.push_back(row);
            // Divide to 2x2 and use rules 2->3
            vector<day21_blk2> blocks;
            for (size_t i=0; i<image.size(); i+=2) {
                for (size_t j=0; j<image.size(); j+=2) {
                    day21_blk2 b(  image[i  ][j  ],image[i  ][j+1],
                                   image[i+1][j  ],image[i+1][j+1]);
                    day21_blk3 b3 = replace<day21_blk2, day21_blk3, day21_rule23>(r23, b);
                    // Place new block in the image
                    size_t i0 = i+i/2; size_t j0 = j+j/2;
                    for (size_t ii=0; ii<3; ii++) {
                        for (size_t jj=0; jj<3; jj++) {
                            new_image[ii+i0][jj+j0] = b3.data[ii][jj];
                        }
                    }
                }
            }
        } else if (image.size() % 3 == 0) {
            // Create new canvas
            size_t new_size = image.size()/3*4;
            vector<bool> row(new_size);
            for (size_t nr = 0; nr<new_size; nr++) new_image.push_back(row);
            // Divide to 3x3 and use rules 3->4
            vector<day21_blk3> blocks;
            for (size_t i=0; i<image.size(); i+=3) {
                for (size_t j=0; j<image.size(); j+=3) {
                    day21_blk3 b(  image[i  ][j  ],image[i  ][j+1],image[i  ][j+2],
                                   image[i+1][j  ],image[i+1][j+1],image[i+1][j+2],
                                   image[i+2][j  ],image[i+2][j+1],image[i+2][j+2]);
                    day21_blk4 b4 = replace<day21_blk3, day21_blk4, day21_rule34>(r34, b);
                    // Place new block in the image
                    size_t i0 = i+i/3; size_t j0 = j+j/3;
                    for (size_t ii=0; ii<4; ii++) {
                        for (size_t jj=0; jj<4; jj++) {
                            new_image[ii+i0][jj+j0] = b4.data[ii][jj];
                        }
                    }
                }
            }
        }
        image = new_image;
    }
    // Count pixels which are ON
    size_t pixels_ON = 0;
    for (size_t i=0; i<image.size(); i++) {
        for (size_t j=0; j<image.size(); j++) {
            if (image[i][j] == ON) pixels_ON++;
        }
    }
    return pixels_ON;
}
