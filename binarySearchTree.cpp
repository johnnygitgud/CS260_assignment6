#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "bstHeaderfortests.h"
class Node {
public:
    std::string fileName;
    Node* left;
    Node* right;

    Node(std::string name) : fileName(name), left(nullptr), right(nullptr) {}
};

class FileBST {
private:
    Node* root;
    std::filesystem::path desktopPath;

    // Helper function to insert a node
    Node* insert(Node* node, std::string fileName) {
        if (node == nullptr) {
            return new Node(fileName);
        }
        if (fileName < node->fileName) {
            node->left = insert(node->left, fileName);
        } else if (fileName > node->fileName) {
            node->right = insert(node->right, fileName);
        }
        return node;
    }

    // Helper function to find the minimum value node. Will be used by remove method
    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // Helper function to delete a node
    Node* remove(Node* node, std::string fileName) {
        if (node == nullptr) {
            return node;
        }
        if (fileName < node->fileName) {
            node->left = remove(node->left, fileName);
        } else if (fileName > node->fileName) {
            node->right = remove(node->right, fileName);
        } else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* temp = findMin(node->right);
            node->fileName = temp->fileName;
            node->right = remove(node->right, temp->fileName);
        }
        return node;
    }

    // Helper function to perform in-order traversal and print filenames in a one line list.
    // void inOrderTraversal(Node* node) {
    //     if (node != nullptr) {
    //         inOrderTraversal(node->left);
    //         std::cout << node->fileName << " ";
    //         inOrderTraversal(node->right);
    //     }
    // }
    
// Helper function to perform in-order traversal and simulate visiting left child, node, and right child.
void inOrderTraversal(Node* node) {
    if (node != nullptr) {
        std::cout << "Visiting left child of " << node->fileName << std::endl;
        inOrderTraversal(node->left);
        std::cout << "Visiting node " << node->fileName << std::endl;
        std::cout << "Visiting right child of " << node->fileName << std::endl;
        inOrderTraversal(node->right);
    }
}
public:
    FileBST() : root(nullptr) {
        // Get the path to the user's Desktop directory
        std::filesystem::path homePath;
        if(const char* env_p = std::getenv("HOME"))
            homePath = env_p;
        else
        {
            const char* env_p2 = std::getenv("USERPROFILE");
            homePath = env_p2;
        }
        desktopPath = homePath / "Desktop";
    }

    void addFile(const std::string& fileName, const std::string& content) {
        std::filesystem::path filePath = desktopPath / fileName;
        // Create the file
        std::ofstream file(filePath);
        if (file) {
            file << content; // Write content to the file
            std::cout << "File created: " << filePath << std::endl;
            file.close();
            root = insert(root, fileName);
        } else {
            std::cerr << "Error creating file: " << filePath << std::endl;
        }
    }

    void removeFile(const std::string& fileName) {
        std::filesystem::path filePath = desktopPath / fileName;
        // Delete the file
        if (std::filesystem::remove(filePath)) {
            std::cout << "File deleted: " << filePath << std::endl;
            root = remove(root, fileName);
        } else {
            std::cerr << "Error deleting file: " << filePath << std::endl;
        }
    }

    void searchFile(const std::string& fileName) {
        Node* current = root;
        while (current != nullptr) {
            if (fileName == current->fileName) {
                std::cout << "File found: " << desktopPath / fileName << std::endl;
                return;
            }
            current = (fileName < current->fileName) ? current->left : current->right;
        }
        std::cout << "File not found: " << desktopPath / fileName << std::endl;
    }

    void traverseFiles() {
        std::cout << "Files in BST (in-order Traversal): ";
        inOrderTraversal(root);
        std::cout << std::endl;
    }
    //Make the desktopPath accessible for testing
    std::filesystem::path getDesktopPath() {
    return desktopPath;
}
};

int main() {
    FileBST fileTree;
    for(int fileNumber = 0; fileNumber < 10; fileNumber++)
    {
        std::string fileName = "file" + std::to_string(fileNumber) + ".txt";
        fileTree.addFile(fileName, "Hello, Instructor Joseph this is " + fileName + "!");
    }
    // Add files with a string to Desktop one at a time.
    // fileTree.addFile("file1.txt", "Hello, this is file1.txt!");
    // fileTree.addFile("file2.txt", "This file contains some data.");

    // Traverse and display files
    fileTree.traverseFiles();

    // // Search for a single file
    fileTree.searchFile("file2.txt");

    //Loop through and search for all files
    for(int fileNumber = 0; fileNumber < 10; fileNumber++)
    {
        std::string fileName = "file" + std::to_string(fileNumber) + ".txt";
        fileTree.searchFile(fileName);
    }

    // Remove one file at a time
    fileTree.removeFile("file2.txt");

    // Traverse again after removal
    fileTree.traverseFiles();

    // Search for the removed file 
    fileTree.searchFile("file2.txt");

    //Loop to remove all files...Uncomment when you want to see all files removed at once. Otherwise all files will not appear in the Desktop after runtime.
    // for(int fileNumber = 0; fileNumber < 10; fileNumber++)
    // {
    //     std::string fileName = "file" + std::to_string(fileNumber) + ".txt";
    //     fileTree.removeFile(fileName);
    // }

    return 0;
}
