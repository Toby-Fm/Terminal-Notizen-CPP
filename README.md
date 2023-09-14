# Terminal Filesystem mit Aufgabenverwaltung
Willkommen zu meinem ersten größeren C++-Projekt! 

# Projektbeschreibung
Dieser Code ermöglicht es, ein kleines Dateisystem im Terminal zu erstellen, das für die Verwaltung von Aufgaben entwickelt wurde. Das Projekt basiert auf der Verwendung einer .txt-Datei, in der Aufgaben gespeichert, abgerufen und gelöscht werden können. Zusätzlich bietet das System die Möglichkeit, Aufgaben einen Status zuzuweisen, entweder "erledigt" (1) oder "nicht erledigt" (0). Damit über seine Aufgaben auch eine bessere übersciht hat.

# Dateisystemfunktionen
das Dateisystem bietet folgende Funktionen:

1. **Aufgaben hinzufügen:** Du kannst neue Aufgaben mit einer detaillierten Beschreibung erstellen.
2. **Aufgaben anzeigen:** Alle vorhandenen Aufgaben werden übersichtlich aufgelistet, um einen klaren Überblick über deine To-Do-Liste zu erhalten.
3. **Aufgaben bearbeiten:** Du kannst den Status einer Aufgabe ändern, um sie als erledigt oder nicht erledigt zu markieren. Oder aber auch die Beschreibung ändern, falls etwas vergessen haben sollte.
4. **Aufgaben löschen:** Aufgaben können einfach aus dem Dateisystem entfernt werden, wenn sie abgeschlossen sind oder nicht mehr benötigt werden.

# Kompilieren des Codes
Um den Code auszuführen, musst du ihn zuerst kompilieren. Verwende dazu den C++-Compiler deiner Wahl.

<pre>
//Für Mac
1. Terminal öffnen
2. cd Pfad/zum/Verzeichnis
3. g++ -std=c++17 index.cpp -o index
</pre>
<pre>
//Für Windows
1. Terminal öffnen
2. cd Pfad/zum/Verzeichnis
3. g++ index.cpp -o index.exe
4. index.exe
</pre>
