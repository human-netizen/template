#include <iostream>
#include <string>
#include <memory>

class TrieNode {
public:
    std::unique_ptr<TrieNode> children[26];  // Array for lowercase English letters
    bool isEndOfWord;
    
    TrieNode() : isEndOfWord(false) {
        // Initialize all children to nullptr
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
};

class Trie {
private:
    std::unique_ptr<TrieNode> root;
    
    // Helper function for prefix search
    bool hasChildren(TrieNode* node) {
        for (int i = 0; i < 26; i++) {
            if (node->children[i] != nullptr) {
                return true;
            }
        }
        return false;
    }
    
    // Helper function for deletion
    bool deleteHelper(TrieNode* node, const std::string& key, int depth = 0) {
        if (node == nullptr) {
            return false;
        }
        
        // Base case: if we've processed all characters
        if (depth == key.length()) {
            if (node->isEndOfWord) {
                node->isEndOfWord = false;
                return !hasChildren(node);
            }
            return false;
        }
        
        int index = key[depth] - 'a';
        if (node->children[index] != nullptr) {
            bool shouldDeleteChild = deleteHelper(node->children[index].get(), key, depth + 1);
            
            if (shouldDeleteChild) {
                node->children[index] = nullptr;
                return !hasChildren(node) && !node->isEndOfWord;
            }
        }
        return false;
    }

public:
    Trie() : root(std::make_unique<TrieNode>()) {}
    
    // Insert a word into the trie
    void insert(const std::string& word) {
        TrieNode* current = root.get();
        
        for (char c : word) {
            int index = c - 'a';
            if (current->children[index] == nullptr) {
                current->children[index] = std::make_unique<TrieNode>();
            }
            current = current->children[index].get();
        }
        current->isEndOfWord = true;
    }
    
    // Search for a word in the trie
    bool search(const std::string& word) const {
        TrieNode* node = root.get();
        
        for (char c : word) {
            int index = c - 'a';
            if (node->children[index] == nullptr) {
                return false;
            }
            node = node->children[index].get();
        }
        return node->isEndOfWord;
    }
    
    // Check if there is any word that starts with the given prefix
    bool startsWith(const std::string& prefix) const {
        TrieNode* node = root.get();
        
        for (char c : prefix) {
            int index = c - 'a';
            if (node->children[index] == nullptr) {
                return false;
            }
            node = node->children[index].get();
        }
        return true;
    }
    
    // Delete a word from the trie
    bool remove(const std::string& word) {
        return deleteHelper(root.get(), word);
    }
    
    // Check if trie is empty
    bool isEmpty() {
        return !hasChildren(root.get());
    }
    TrieNode *getRoot(){
        return root.get();
    }
};

// Example usage
int main() {
    Trie trie;
    
    // Insert some words
    trie.insert("apple");
    trie.insert("app");
    trie.insert("apricot");
    
    // Search demonstrations
    std::cout << "Search 'apple': " << (trie.search("apple") ? "Found" : "Not found") << std::endl;
    std::cout << "Search 'app': " << (trie.search("app") ? "Found" : "Not found") << std::endl;
    std::cout << "Search 'apt': " << (trie.search("apt") ? "Found" : "Not found") << std::endl;
    
    // Prefix search demonstrations
    std::cout << "Prefix 'app': " << (trie.startsWith("app") ? "Found" : "Not found") << std::endl;
    std::cout << "Prefix 'apt': " << (trie.startsWith("apt") ? "Found" : "Not found") << std::endl;
    
    // Delete demonstration
    std::cout << "Removing 'apple'" << std::endl;
    trie.remove("apple");
    std::cout << "Search 'apple': " << (trie.search("apple") ? "Found" : "Not found") << std::endl;
    std::cout << "Search 'app': " << (trie.search("app") ? "Found" : "Not found") << std::endl;
    
    return 0;
}