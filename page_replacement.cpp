#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

// FIFO Page Replacement Algorithm
int fifo(vector<int>& pages, int frames) {
    queue<int> memory;
    unordered_map<int, bool> inMemory;
    int page_faults = 0;

    for (int page : pages) {
        if (!inMemory[page]) {
            if (memory.size() < frames) {
                memory.push(page);
                inMemory[page] = true;
            } else {
                int oldest = memory.front();
                memory.pop();
                inMemory[oldest] = false;
                memory.push(page);
                inMemory[page] = true;
            }
            page_faults++;
        }
        cout << "Page: " << page << " -> Memory: ";
        queue<int> temp = memory;
        while (!temp.empty()) {
            cout << temp.front() << " ";
            temp.pop();
        }
        cout << endl;
    }
    return page_faults;
}

// LRU Page Replacement Algorithm
int lru(vector<int>& pages, int frames) {
    vector<int> memory;
    unordered_map<int, int> recent;
    int page_faults = 0;

    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];
        auto it = find(memory.begin(), memory.end(), page);
        if (it == memory.end()) {
            if (memory.size() < frames) {
                memory.push_back(page);
            } else {
                int lru_page = distance(memory.begin(), min_element(memory.begin(), memory.end(), [&](int a, int b) {
                    return recent[a] < recent[b];
                }));
                memory[lru_page] = page;
            }
            page_faults++;
        }
        recent[page] = i;
        cout << "Page: " << page << " -> Memory: ";
        for (int p : memory) {
            cout << p << " ";
        }
        cout << endl;
    }
    return page_faults;
}

// Optimal Page Replacement Algorithm
int optimal(vector<int>& pages, int frames) {
    vector<int> memory;
    int page_faults = 0;

    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];
        if (find(memory.begin(), memory.end(), page) == memory.end()) {
            if (memory.size() < frames) {
                memory.push_back(page);
            } else {
                int farthest = -1, replaceIndex = -1;
                for (int j = 0; j < memory.size(); j++) {
                    int nextUse = find(pages.begin() + i + 1, pages.end(), memory[j]) - pages.begin();
                    if (nextUse > farthest) {
                        farthest = nextUse;
                        replaceIndex = j;
                    }
                }
                memory[replaceIndex] = page;
            }
            page_faults++;
        }
        cout << "Page: " << page << " -> Memory: ";
        for (int p : memory) {
            cout << p << " ";
        }
        cout << endl;
    }
    return page_faults;
}

int main() {
    vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int frames = 3;

    // FIFO Algorithm
    cout << "FIFO Page Replacement:\n";
    int fifo_faults = fifo(pages, frames);
    cout << "Total Page Faults (FIFO): " << fifo_faults << "\n\n";

    // LRU Algorithm
    cout << "LRU Page Replacement:\n";
    int lru_faults = lru(pages, frames);
    cout << "Total Page Faults (LRU): " << lru_faults << "\n\n";

    // Optimal Algorithm
    cout << "Optimal Page Replacement:\n";
    int optimal_faults = optimal(pages, frames);
    cout << "Total Page Faults (Optimal): " << optimal_faults << "\n\n";

    return 0;
}

