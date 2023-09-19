#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

// Definition einer Struktur namens "Task" zur Darstellung von Aufgaben
struct Task {
    std::string description;
    bool completed;
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

// Funktion zur Verarbeitung von Aufgaben in einem Verzeichnis
void processTasksInDirectory(const std::string& directoryPath) {
    std::vector<Task> tasks; // Erstellen einer Liste für Aufgaben
    std::string filename = directoryPath + "/tasks.txt"; // Dateipfad für die Aufgabenliste/Output Text File

    loadTasksFromFile(tasks, filename); // Laden der gespeicherten Aufgaben beim Programmstart

    char choice;
    do {
        std::cout << "\n--- Hauptmenu ---\n";
        std::cout << "0. Beenden\n"; // Beendet das Programm
        std::cout << "1. Verzeichnis Anzeigen\n"; // Zeigt alle Ordner und Dateien aus dem Verzeichnis
        std::cout << "\n" << "Ihre Auswahl: ";
        std::cin >> choice;

        switch (choice) {
            // 0 => Beendet das Programm.
            // 1 => Zeigt das Verzeichnis des Main Ordners an.
            case '1': {
                std::cout << "\n" << "Inhalt des Ordners: \n" << directoryPath << "\n\n"; // Zeigt den Inhalt des Ordners an. + Das Verzeichnis
                for (const auto& entry : fs::directory_iterator(directoryPath)) {
                    if (entry.is_directory()) {
                        std::cout << "[Ordner]: " << entry.path().filename() << "\n"; // Schreibt vor einem Ordner "Ordner".
                    } else {
                        std::cout << "[Datei]: " << entry.path().filename() << "\n"; // Schreibt vor einer Datei "Datei".
                    }
                }
                char newChoice;
                do {
                    std::cout << "\n--- Auswahl ---\n";
                    std::cout << "0. Zurück ins Hauptmenu\n";
                    std::cout << "1. In Ordner navigieren\n";
                    std::cout << "2. Ordner erstellen\n";
                    std::cout << "3. Ordner oder Datei löschen\n";
                    std::cout << "4. Text-Datei öffnen/bearbeiten\n";
                    std::cout << "5. Text-Datei erstellen\n";
                    std::cout << "6. Text-Datei löschen\n";
                    std::cout << "\n" << "Ihre Auswahl: ";
                    std::cin >> newChoice;

                    switch (newChoice) {
                        // 0 => Geht zurück ins Hauptmenu.
                        // 1 => Ruft den angegebenen Ordner auf und Navigiert rein.
                        case '1': {
                            std::string input;
                            std::cout << "Bitte geben Sie den Namen des Ordners ein, den Sie öffnen möchten: ";
                            std::cin >> input;

                            std::string folderPath = directoryPath + "/" + input;
                            std::cout << "In den Ordner '" << folderPath << "' navigiert." << std::endl;

                            // Rekursiver Aufruf der Funktion für das Unterverzeichnis
                            processTasksInDirectory(folderPath);
                            break;
                        }
                        case '2': {
                            std::string folderName;
                            std::cout << "Name des neuen Ordners (Leerzeichen müssen mit '_' markiert werden): ";
                            std::cin >> folderName;

                            std::string folderPath = directoryPath + "/" + folderName;
                            if (fs::create_directory(folderPath)) {
                                // Ordner konnte erstellt werden.
                                std::cout << "\nOrdner wurde erstellt. \n" 
                                          << "Name des Ordners: " << folderName << "\n" 
                                          << "Verzeichnis: " << folderPath << std::endl;
                            } else {
                                std::cerr << "Fehler beim Erstellen des Ordners." << std::endl;
                            }
                            break;
                        }
                        case '3': {
                            if (!tasks.empty()) {
                                std::cout << "+-----------------------------------------------------------------------------------------+ \n";
                                std::cout << "| Wenn eine Datei entfernt werden soll, muss der ganze Name angegeben werden. => entf.txt | \n";
                                std::cout << "+-----------------------------------------------------------------------------------------+ \n";

                                std::string itemName;
                                std::cout << "Welcher Ordner oder Datei soll entfernt werden?: ";
                                std::cin >> itemName;
                                bool found = false;

                                for (const auto& entry : fs::directory_iterator(directoryPath)) {
                                    if (entry.is_directory() || entry.is_regular_file()) {
                                        std::string entryName = entry.path().filename().string();
                                        if (entryName == itemName) {
                                            fs::remove(entry); // Löschen des Ordners oder der Datei
                                            std::cout << "Element '" << itemName << "' entfernt.\n";
                                            found = true;
                                            break;
                                        }
                                    }
                                }
                                if (!found) {
                                    std::cerr << "Element '" << itemName << "' wurde nicht gefunden oder konnte nicht entfernt werden.\n";
                                }
                            }
                            break;
                        }
                        case '4': {
                            std::string input;
                            std::cout << "Bitte geben Sie den Namen der Datei ein, die Sie anzeigen/bearbeiten möchten: ";
                            std::cin >> input;

                            std::string filename = directoryPath + "/" + input;

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
                        case '5': {
                            std::string input;
                            std::cout << "Bitte geben Sie den Namen der neuen Textdatei ein: ";
                            std::cin >> input;

                            std::string newFilename = directoryPath + "/" + input;

                            // Überprüfen, ob die Datei bereits existiert
                            if (fs::exists(newFilename)) {
                                std::cout << "Die Datei existiert bereits." << std::endl;
                            } else {
                                std::ofstream newFile(newFilename);
                                if (newFile.is_open()) {
                                    newFile.close();
                                    std::cout << "Textdatei '" << input << "' wurde erstellt." << std::endl;
                                } else {
                                    std::cerr << "Fehler beim Erstellen der Textdatei." << std::endl;
                                }
                            }
                            break;
                        }
                        case '6': {
                            std::string input;
                            std::cout << "Bitte geben Sie den Namen der Textdatei ein, die Sie löschen möchten: ";
                            std::cin >> input;

                            std::string deleteFilename = directoryPath + "/" + input;

                            // Überprüfen, ob die Datei existiert und löschen
                            if (fs::exists(deleteFilename)) {
                                fs::remove(deleteFilename);
                                std::cout << "Textdatei '" << input << "' wurde gelöscht." << std::endl;
                            } else {
                                std::cerr << "Die Datei existiert nicht oder konnte nicht gelöscht werden." << std::endl;
                            }
                            break;
                        }
                    }
                } while (newChoice != '0'); // Schleife läuft, bis die Auswahl "0" (Zurück) getroffen wird.
                break;
            }
        }
    } while (choice != '0'); // Schleife läuft, bis die Auswahl "0" (Beenden) getroffen wird.

    saveTasksToFile(tasks, filename); // Speichern der Aufgaben beim Programmende
}

int main() {
    std::string onedrivePath = "C:\\Users\\tobyw\\OneDrive\\Notizen"; // Verzeichnis deines OneDrive-Ordners
    processTasksInDirectory(onedrivePath); // Starte die Verarbeitung im Hauptverzeichnis

    return 0;
}
