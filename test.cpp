#include <cassert>
#include <sstream>
#include <iostream>
#include <filesystem>
#include "bstHeaderfortests.h"

void testAddFile() {
    FileBST fileTree;
    fileTree.addFile("test.txt", "This is a test file.");
    // Check if the file was added correctly
    // This will depend on your filesystem and may need to be adjusted
    assert(std::filesystem::exists(fileTree.getDesktopPath() / "test.txt"));
}

void testRemoveFile() {
    FileBST fileTree;
    fileTree.addFile("test.txt", "This is a test file.");
    fileTree.removeFile("test.txt");
    // Check if the file was removed correctly
    // This will depend on your filesystem and may need to be adjusted
    assert(!std::filesystem::exists(fileTree.getDesktopPath() / "test.txt"));
}

void testSearchFile() {
    FileBST fileTree;
    fileTree.addFile("test.txt", "This is a test file.");
    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());
    fileTree.searchFile("test.txt");
    std::cout.rdbuf(prevcoutbuf);
    // Check if the correct output was printed
    assert(buffer.str() == "File found: " + (fileTree.getDesktopPath() / "test.txt").string() + "\n");
}

void testTraverseFiles() {
    FileBST fileTree;
    fileTree.addFile("test1.txt", "This is a test file.");
    fileTree.addFile("test2.txt", "This is another test file.");
    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());
    fileTree.traverseFiles();
    std::cout.rdbuf(prevcoutbuf);
    // Check if the correct output was printed
    assert(buffer.str() == "Files in BST (in-order Traversal): Visiting left child of test1.txt\nVisiting node test1.txt\nVisiting right child of test1.txt\nVisiting left child of test2.txt\nVisiting node test2.txt\nVisiting right child of test2.txt\n\n");
}

int main() {
    testAddFile();
    testRemoveFile();
    testSearchFile();
    testTraverseFiles();
    return 0;
}