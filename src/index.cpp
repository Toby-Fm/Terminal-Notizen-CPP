#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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
            std::cout << (i + 1) << ". "; // Nummerierung der Aufgaben
            if (tasks[i].completed) {
                std::cout << "[X] "; // Anzeige eines erledigten Status
            } else {
                std::cout << "[ ] "; // Anzeige eines nicht erledigten Status
            }
            std::cout << tasks[i].description << "\n"; // Anzeige der Aufgabenbeschreibung
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

int main() {
    std::vector<Task> tasks; // Erstellen einer Liste für Aufgaben
    std::string filename = "/components/tasks.txt"; // Dateipfad für die Aufgabenliste/ Output Text File
    loadTasksFromFile(tasks, filename); // Laden der gespeicherten Aufgaben beim Programmstart

    char choice;
    do {
        std::cout << "\n--- ToDo-Liste ---\n"; // Hauptmenü für die ToDo-Liste
        std::cout << "1. Aufgabe hinzufügen\n";
        std::cout << "2. Aufgaben anzeigen\n";
        std::cout << "3. Aufgabe entfernen\n";
        std::cout << "4. Beenden\n";
        std::cout << "Ihre Auswahl: ";
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
                showTasks(tasks); // Anzeigen der Aufgaben

                std::string input;
                std::cout << "\nIch möchte den Status einer Aufgabe ändern. (Ändern/Nein)";
                std::cout << "\nIch möchte die Beschreibung einer Aufgabe ändern. (Ja/Nein)" << std::endl;
                std::cout << "Ihre Auswahl: ";
                std::cin >> input;

                if (input == "Ändern" || input == "ändern") { // Wenn der Benutzer "Ändern" oder "ändern" eingibt
                    int index;
                    std::cout << "Index der zu ändernden Aufgabe: ";
                    std::cin >> index;

                    if (index >= 1 && index <= static_cast<int>(tasks.size())) { // Überprüfen, ob der eingegebene Index gültig ist
                        std::string newStatus;
                        std::cout << "Neuer Status (1 für erledigt, 0 für nicht erledigt): ";
                        std::cin >> newStatus;

                        if (newStatus == "1" || newStatus == "0") { // Überprüfen, ob der eingegebene Status gültig ist
                            // Ändern des Status der ausgewählten Aufgabe im Vektor tasks
                            tasks[index - 1].completed = (newStatus == "1");
                            std::cout << "Status der Aufgabe " << index << " wurde geändert." << std::endl;
                            saveTasksToFile(tasks, filename);
                        } else {
                            std::cout << "Ungültiger Status. Der Status sollte 1 oder 0 sein." << std::endl;
                        }
                    } else {
                        std::cout << "Ungültiger Index." << std::endl;
                    }
                } 
                else if (input == "Nein" || input == "nein") { // Wenn der Benutzer "Nein" oder "nein" eingibt
                    std::cout << "\nWieder im Menu\n";
                    break; // Beenden der Schleife und zurück zum Hauptmenü
                }
                else if (input == "Ja" || input == "ja") { // Wenn der Benutzer "Ja" oder "ja" eingibt
                    int index;
                    std::cout << "Index der zu ändernden Aufgabe: ";
                    std::cin >> index;

                    if (index >= 1 && index <= static_cast<int>(tasks.size())) { // Überprüfen, ob der eingegebene Index gültig ist
                        std::string newDescription;
                        std::cout << "Neue Beschreibung: ";
                        std::cin.ignore();
                        std::getline(std::cin, newDescription); // Beschreibung einlesen

                        // Ändern der Beschreibung der ausgewählten Aufgabe im Vektor tasks
                        tasks[index - 1].description = newDescription;
                        std::cout << "Beschreibung der Aufgabe " << index << " wurde geändert." << std::endl;
                        saveTasksToFile(tasks, filename);
                    } else {
                        std::cout << "Ungültiger Index." << std::endl;
                    }
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
                std::cout << "Programm wird beendet.\n";
                break;
            }
            default: {
                std::cout << "Ungültige Auswahl. Bitte erneut versuchen.\n"; // Fehlermeldung bei ungültiger Auswahl
                break;
            }
        }
    } while (choice != '4'); // Schleife läuft, bis die Auswahl '4' (Beenden) getroffen wird

    return 0;
}
