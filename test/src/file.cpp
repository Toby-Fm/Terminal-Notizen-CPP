#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>

namespace fs = std::__fs::filesystem;

//Definition einer Struktur namens "Task" zur Darstellung von Aufgaben
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

int main() {
    std::vector<Task> tasks; // Erstellen einer Liste für Aufgaben
    // Aktualisiere den Dateipfad entsprechend deines OneDrive-Ordners
    std::string onedrivePath = "/Users/tobywichmann/Library/CloudStorage/OneDrive-Persönlich/Notizen/";
    std::string filename = onedrivePath + ".txt"; // Dateipfad für die Aufgabenliste/Output Text File

    loadTasksFromFile(tasks, filename); // Laden der gespeicherten Aufgaben beim Programmstart

    char choice;
    do {
        std::cout << "\n--- Hauptmenu ---\n";
        std::cout << "0. Beenden\n"; //Beendet das Programm
        std::cout << "1. Verzeichnis Anzeigen\n"; //Zeigt alle Ordner und Dateien aus dem Verzeichnis
        std::cout << "\n" << "Ihre Auswahl: ";
        std::cin >> choice;

        switch (choice) {
            // 0 => Beendet das Programm.
            // 1 => Zeigt das Verzeichnis des Main Ordners an.
            case '1': {
                std::cout << "\n" << "Inhalt des Ordners: \n" << onedrivePath << "\n\n"; //Zeigt den Inhalt des Ordners an. + Das Verzeichnis
                for (const auto& entry : fs::directory_iterator(onedrivePath)) {
                    if (entry.is_directory()) {
                        std::cout << "[Ordner]: " << entry.path().filename() << "\n"; //Schreibt vor einem Ordner "Ordner".
                    } else {
                        std::cout << "[Datei]: " << entry.path().filename() << "\n"; //Schreibt vor einer Datei "Datei".
                    }
                }
                char newChoice;
                do {
                    std::cout << "\n--- Auswahl ---\n";
                    std::cout << "0. Zurück ins Hauptmenu\n";
                    std::cout << "1. In Ordner navigieren\n";
                    std::cout << "2. Ordner erstellen\n";
                    std::cout << "3. Ordner oder Datei löschen\n";
                    std::cout << "\n" << "Ihre Auswahl: ";
                    std::cin >> newChoice;

                    switch (newChoice) {
                        //0 => Geht zurück ins Hauptmenu.
                        //1 => Ruft den angegebenen Ordner auf und Navigiert rein.
                        case '1': {
                            std::string input;
                            std::cout << "Bitte geben Sie den Namen des Ordners ein, den Sie öffnen möchten: ";
                            std::cin >> input;

                            std::string folderPath = onedrivePath + input;
                            std::cout << "In den Ordner '" << folderPath << " navigiert." << std::endl;
                            break;
                        }
                        case '2': {
                            std::string folderName;
                            std::cout << "Name des neuen Ordners (Leerzeichen müssen mit '_' makiert werden): ";
                            std::cin >> folderName;

                            std::string folderPath = onedrivePath + folderName;
                            if (fs::create_directory(folderPath)) {
                                //Ordner konnte erstellt werden.
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
                                std::cout << "Welcher Ordner oder Datei soll entfernt werde?: ";
                                std::cin >> itemName;
                                bool found = false;

                                for (const auto& entry : fs::directory_iterator(onedrivePath)) {
                                    if (entry.is_directory() || entry.is_regular_file()) {
                                        std::string entryName = entry.path().filename().string();
                                        if (entryName == itemName) {
                                            fs::remove(entry); // Löschen des Ordners oder der Datei
                                            std::cout << "Element " << itemName << " entfernt.\n";
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
                    }

                } while (newChoice != '0'); // Schleife läuft, bis die Auswahl "0" (Zurück) getroffen wird.
                break;
            }
        }

    } while (choice != '0'); // Schleife läuft, bis die Auswahl "0" (Beenden) getroffen wird.

    return 0;
}