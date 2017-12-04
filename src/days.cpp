#include "days.h"

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