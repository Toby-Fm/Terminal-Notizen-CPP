#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>

namespace fs = std::__fs::filesystem;

// Definition einer Struktur namens "Task" zur Darstellung von Aufgaben
struct Task {
    std::string description; // Beschreibung der Aufgabe
    bool completed; // Gibt an, ob die Aufgabe abgeschlossen ist (true) oder nicht (false)
};

// Funktion zur Anzeige der Aufgaben in der Liste
void showTasks(const std::vector<Task>& tasks) {
    if (tasks.empty()) { // Wenn die Aufgabenliste leer ist
        std::cout << "+---------------------+\n";
        std::cout << "| Die Liste ist leer. |\n";
        std::cout << "+---------------------+\n";
    } else {
        std::cout << "\n--- Aufgaben ---\n"; // Überschrift für die Aufgabenliste
        for (size_t i = 0; i < tasks.size(); ++i) { // Schleife durch die Aufgaben
            std::cout << "+-----------------------------------+\n";
            std::cout << "|" << (i + 1) << ". "; // Nummerierung der Aufgaben
            if (tasks[i].completed) {
                std::cout << "[X] "; // Anzeige eines erledigten Status
            } else {
                std::cout << "[ ] "; // Anzeige eines nicht erledigten Status
            }
            std::cout << tasks[i].description << "\n"; // Anzeige der Aufgabenbeschreibung
            std::cout << "+-----------------------------------+\n";
        }
    }
}

// Funktion zum Speichern der Aufgaben in eine Datei
void saveTasksToFile(const std::vector<Task>& tasks, const std::string& filename) {
    std::ofstream file(filename); // Öffnen der Datei für den Schreibzugriff
    if (!file.is_open()) {
        std::cout << "+-----------------------------------------------------------------------------------+\n";
        std::cerr << "Fehler beim Speichern der Aufgaben. Datei konnte nicht geöffnet werden: " << filename << std::endl; // Fehlermeldung bei Problemen mit dem Dateizugriff
        std::cout << "+-----------------------------------------------------------------------------------+\n";
        return;
    }
    for (const Task& task : tasks) {
        file << task.description << "," << (task.completed ? "1" : "0") << "\n"; // Schreiben der Aufgaben in die Datei
    }
    file.close(); // Schließen der Datei nach dem Schreiben
}

// Funktion zum Laden der Aufgaben aus einer Datei
void loadTasksFromFile(std::vector<Task>& tasks, const std::string& filename) {
    std::ifstream file(filename); // Öffnen der Datei für den Lesezugriff
    if (!file.is_open()) {
        std::cerr << "Keine gespeicherten Aufgaben gefunden." << std::endl; // Fehlermeldung, wenn keine Datei gefunden wird
        return;
    }
    tasks.clear(); // Löschen der aktuellen Aufgabenliste
    std::string line;
    while (std::getline(file, line)) { // Einlesen der Aufgaben aus der Datei
        size_t commaPos = line.find(',');
        if (commaPos != std::string::npos) {
            Task task;
            task.description = line.substr(0, commaPos); // Extrahieren der Aufgabenbeschreibung
            task.completed = (line.substr(commaPos + 1) == "1"); // Überprüfen des Aufgabenstatus
            tasks.push_back(task); // Hinzufügen der Aufgabe zur Liste
        }
    }
    file.close(); // Schließen der Datei nach dem Lesen
}
// Funktion zur Bearbeitung von Aufgaben
void editTask(std::vector<Task>& tasks) {
    showTasks(tasks); // Anzeigen der Aufgaben

    int index;
    std::cout << "Index der zu bearbeitenden Aufgabe: ";
    std::cin >> index;

    if (index >= 1 && index <= static_cast<int>(tasks.size())) { // Überprüfen, ob der eingegebene Index gültig ist
        std::string input;
        std::cout << "Möchten Sie die Beschreibung ändern? (Ja/Nein): ";
        std::cin >> input;

        if (input == "Ja" || input == "ja") {
            std::string newDescription;
            std::cout << "Neue Beschreibung: ";
            std::cin.ignore();
            std::getline(std::cin, newDescription); // Beschreibung einlesen
            tasks[index - 1].description = newDescription; // Ändern der Beschreibung
            std::cout << "\nBeschreibung der Aufgabe " << index << " wurde geändert." << std::endl;
        }

        std::cout << "Möchten Sie den Status ändern? (Ja/Nein): ";
        std::cin >> input;

        if (input == "Ja" || input == "ja") {
            std::string newStatus;
            std::cout << "Neuer Status (1 für erledigt, 0 für nicht erledigt): ";
            std::cin >> newStatus;

            if (newStatus == "1" || newStatus == "0") {
                tasks[index - 1].completed = (newStatus == "1"); // Ändern des Status
                std::cout << "\nStatus der Aufgabe " << index << " wurde geändert." << std::endl;
            } else {
                std::cout << "\nUngültiger Status. Der Status sollte 1 oder 0 sein." << std::endl;
            }
        }
    } else {
        std::cout << "Ungültiger Index." << std::endl;
    }
}

int main() {
    std::vector<Task> tasks; // Erstellen einer Liste für Aufgaben
    // Aktualisiere den Dateipfad entsprechend deines OneDrive-Ordners
    std::string onedrivePath = "/Users/tobywichmann/Library/CloudStorage/OneDrive-Persönlich/Notizen/";
    std::string filename = onedrivePath + ".txt"; // Dateipfad für die Aufgabenliste/Output Text File

    loadTasksFromFile(tasks, filename); // Laden der gespeicherten Aufgaben beim Programmstart

    char choice;
    do {
        std::cout << "\n--- Haupt Menu ---\n"; // Hauptmenü für die ToDo-Liste
        std::cout << "1. Aufgabe hinzufügen\n";
        std::cout << "2. Aufgaben anzeigen/ändern\n";
        std::cout << "3. Aufgabe entfernen\n";
        std::cout << "4. Ordner erstellen\n"; // Option zum Ordner erstellen hinzugefügt
        std::cout << "5. Ordner anzeigen\n";
        std::cout << "7. In Ordner navigieren\n";
        std::cout << "9. Beenden\n";
        std::cout << "\n" << "Ihre Auswahl: ";
        std::cin >> choice;

        switch (choice) {
            //case 1: Aufgabe hinzufügen
            case '1': {
                std::string input;
                std::cout << "Möchten Sie eine Aufgabe hinzufügen? (Ja/Nein): ";
                std::cin >> input;
                if (input == "Ja" || input == "ja") {
                    Task task;
                    std::cout << "Beschreibung der Aufgabe: ";
                    std::cin.ignore();
                    std::getline(std::cin, task.description); // Eingabe der Aufgabenbeschreibung
                    task.completed = false;
                    tasks.push_back(task); // Hinzufügen der neuen Aufgabe zur Liste
                    std::cout << "Aufgabe hinzugefügt.\n";
                    saveTasksToFile(tasks, filename); // Speichern der aktualisierten Liste in die Datei
                }
                break;
            }
            //case 2 Aufgaben Anzeigen / Ändern / Status setzen
            case '2': {
                std::string input;
                std::cout << "Bitte geben Sie den Namen der Datei ein, die Sie anzeigen/bearbeiten möchten: ";
                std::cin >> input;

                std::string filename = onedrivePath + input;

                // Überprüfen, ob die Datei existiert, bevor wir sie öffnen
                std::ifstream file(filename);
                if (file.is_open()) {
                    file.close(); // Datei schließen

                    // Datei existiert, also können wir Aufgaben laden
                    loadTasksFromFile(tasks, filename); // Laden der Aufgaben aus der Datei
                    showTasks(tasks); // Anzeigen der Aufgaben aus der Datei

                    // Menü für Bearbeitung oder Hinzufügen
                    char editOrAdd;
                    std::cout << "Möchten Sie Aufgaben bearbeiten (B) oder eine Aufgabe hinzufügen (H)? ";
                    std::cin >> editOrAdd;
                    if (editOrAdd == 'B' || editOrAdd == 'b') {
                        editTask(tasks); // Bearbeiten von Aufgaben aus der Datei
                    } else if (editOrAdd == 'H' || editOrAdd == 'h') {
                        std::string input;
                        std::cout << "Möchten Sie eine Aufgabe hinzufügen? (Ja/Nein): ";
                        std::cin >> input;
                        if (input == "Ja" || input == "ja") {
                            Task task;
                            std::cout << "Beschreibung der Aufgabe: ";
                            std::cin.ignore();
                            std::getline(std::cin, task.description); // Eingabe der Aufgabenbeschreibung
                            task.completed = false;
                            tasks.push_back(task); // Hinzufügen der neuen Aufgabe zur Liste
                            std::cout << "Aufgabe hinzugefügt.\n";
                            saveTasksToFile(tasks, filename); // Speichern der aktualisierten Liste in die Datei
                        }
                        break;
                    } else {
                        std::cout << "Ungültige Auswahl." << std::endl;
                    }

                    saveTasksToFile(tasks, filename); // Speichern der aktualisierten Liste in die Datei
                } else {
                    std::cout << "Die Datei existiert nicht oder konnte nicht geöffnet werden." << std::endl;
                }
                break;
            }
            //case '3': Löschen einer Aufgabe
            case '3': {
                showTasks(tasks); // Anzeigen der Aufgaben vor dem Entfernen
                if (!tasks.empty()) {
                    int index;
                    std::cout << "Index der zu entfernenden Aufgabe: ";
                    std::cin >> index;
                    if (index >= 1 && index <= static_cast<int>(tasks.size())) {
                        tasks.erase(tasks.begin() + index - 1); // Entfernen der ausgewählten Aufgabe
                        std::cout << "Aufgabe entfernt.\n";
                        saveTasksToFile(tasks, filename); // Speichern der aktualisierten Liste in die Datei
                    } else {
                        std::cout << "Ungültiger Index.\n"; // Fehlermeldung bei ungültigem Index
                    }
                }
                break;
            }
            case '4': {
                std::string folderName;
                std::cout << "Name des neuen Ordners: ";
                std::cin >> folderName;

                std::string folderPath = onedrivePath + folderName;
                if (fs::create_directory(folderPath)) {
                    std::cout << "Ordner erstellt: " << folderPath << std::endl;
                } else {
                    std::cerr << "Fehler beim Erstellen des Ordners." << std::endl;
                }
                break;
            }
            case '5': {
                std::cout << "\n" << "Inhalt des Ordners " << onedrivePath << ":\n\n";
                for (const auto& entry : fs::directory_iterator(onedrivePath)) {
                    if (entry.is_directory()) {
                        std::cout << "[Verzeichnis] " << entry.path().filename() << "\n";
                    } else {
                        std::cout << "[Datei] " << entry.path().filename() << "\n";
                    }
                }
                break;
            }
            case '7': {
                std::string input;
                std::cout << "Bitte geben Sie den Namen des Ordners ein, den Sie öffnen möchten: ";
                std::cin >> input;

                std::string folderPath = onedrivePath + input;

                // Hier kannst du die Logik zum Navigieren in den Ordner hinzufügen
                // Dies kann das Auflisten von Dateien und Unterordnern im ausgewählten Ordner usw. beinhalten

                // Beispiel:
                std::cout << "In den Ordner '" << folderPath << "' navigiert." << std::endl;

                // Nachdem du in den Ordner navigiert bist, kannst du die .txt Datei erstellen
                std::string txtFileName;
                std::cout << "Bitte geben Sie den Namen der .txt Datei ein, die Sie erstellen möchten: ";
                std::cin >> txtFileName;

                std::string txtFilePath = folderPath + "/" + txtFileName + ".txt"; // Pfad für die .txt Datei im Ordner

                // Hier kannst du die Logik zum Erstellen der .txt Datei im ausgewählten Ordner hinzufügen
                // Dies kann das Erstellen einer leeren .txt Datei usw. beinhalten

                // Beispiel: Erstellung einer leeren .txt Datei
                std::ofstream txtFile(txtFilePath);
                if (txtFile.is_open()) {
                    txtFile.close();
                    std::cout << "Die Datei '" << txtFileName << ".txt' wurde im Ordner '" << folderPath << "' erstellt." << std::endl;
                } else {
                    std::cerr << "Fehler beim Erstellen der Datei." << std::endl;
                }

                break;
            }
        }
    } while (choice != '6'); // Schleife läuft, bis die Auswahl '4' (Beenden) getroffen wird

    return 0;
}
