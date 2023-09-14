#include <iostream>
#include <filesystem>

namespace fs = std::__fs::filesystem;

int main() {
    std::string folderName;
    std::cout << "Name des neuen Ordners: ";
    std::cin >> folderName;

    // Der Ordner wird im aktuellen Arbeitsverzeichnis erstellt
    fs::path folderPath = folderName;

    try {
        // Versuche, den Ordner zu erstellen
        fs::create_directory(folderPath);
        std::cout << "Ordner erstellt: " << folderPath << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "Fehler beim Erstellen des Ordners: " << ex.what() << std::endl;
    }

    return 0;
}
