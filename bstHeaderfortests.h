// bstHeaderfortests.h
#ifndef BSTHEADERFORTESTS_H
#define BSTHEADERFORTESTS_H

#include <string>
#include <filesystem>
//Node declaration
class Node {
public:
    std::string fileName;
    Node* left;
    Node* right;

    Node(std::string name);
};
//BST declaration
class FileBST {
private:
    Node* root;
    std::filesystem::path desktopPath;

    Node* insert(Node* node, std::string fileName);
    Node* findMin(Node* node);
    Node* remove(Node* node, std::string fileName);
    void inOrderTraversal(Node* node);

public:
    FileBST();
    void addFile(const std::string& fileName, const std::string& content);
    void removeFile(const std::string& fileName);
    void searchFile(const std::string& fileName);
    void traverseFiles();
    std::filesystem::path getDesktopPath();
};

#endif // BSTHEADERFORTESTS_H