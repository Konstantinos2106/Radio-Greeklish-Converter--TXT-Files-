# Radio-Greeklish-Converter-TXT-Files

Ένα ελαφρύ Windows GUI εργαλείο για web radio broadcasters. Διαβάζει αυτόματα τους ελληνικούς τίτλους τραγουδιών από ένα αρχείο TXT "Now Playing", τους μετατρέπει σε Greeklish και εξάγει ένα καθαρό αρχείο για streaming software όπως το [BUTT](https://danielnoethen.de/butt/), λύνοντας όλα τα προβλήματα κωδικοποίησης.

Μια ελαφριά, αυτοματοποιημένη εφαρμογή για Windows γραμμένη σε C, που λύνει το συνηθισμένο πρόβλημα κωδικοποίησης κειμένου για τους παραγωγούς ελληνικών διαδικτυακών ραδιοφώνων.

Πολλά εργαλεία μετάδοσης (όπως το [BUTT](https://danielnoethen.de/butt/)) δυσκολεύονται να εμφανίσουν σωστά τους ελληνικούς UTF-8 χαρακτήρες στα μεταδεδομένα (metadata) του "Now Playing". Αυτό το εργαλείο λειτουργεί ως γέφυρα: διαβάζει το τρέχον κομμάτι από το αρχείο κειμένου που εξάγει ο player σας (π.χ. [AIMP](https://aimp.ru/) με το πρόσθετο [_Current Track Info to Any_](https://aimp.ru/?do=catalog&rec_id=358)), μετατρέπει αμέσως τους ελληνικούς χαρακτήρες σε Greeklish (Λατινικό αλφάβητο) και γράφει το καθαρό, έτοιμο για streaming κείμενο σε ένα νέο αρχείο.

**Μπορείτε να κατεβάσε το `.c`αρχείο [εδώ](https://github.com/Konstantinos2106/Radio-Greeklish-Converter--TXT-Files-/raw/refs/heads/main/radio_greeklish.c)**

## Χαρακτηριστικά

* **Έξυπνη Μηχανή Μετατροπής:** Μετατρέπει με ακρίβεια τους ελληνικούς χαρακτήρες σε λατινικούς, συμπεριλαμβανομένων των δίψηφων φωνηέντων (ου, αυ, ει) και των τονισμένων γραμμάτων, ενώ καθαρίζει και τους "ορφανούς" τόνους (floating accents).

* **Παρακολούθηση σε Πραγματικό Χρόνο:** Ελέγχει το αρχείο εισόδου κάθε 2 δευτερόλεπτα και ενημερώνει το αρχείο εξόδου μόνο όταν το τραγούδι αλλάζει πραγματικά, εξοικονομώντας πόρους από τον δίσκο (disk I/O).

* **Σύγχρονο Windows GUI:** Χτισμένο με το εγγενές Win32 API, διαθέτει ένα καθαρό περιβάλλον Dark Mode με έντονες Neon Blue λεπτομέρειες.

* **Μηδενική Κατανάλωση CPU:** Εξαιρετικά ελαφρύ, πράγμα που σημαίνει ότι δεν θα επηρεάσει καθόλου την απόδοση του λογισμικού μετάδοσης ήχου.

* **Διαχείριση BOM:** Εντοπίζει και παρακάμπτει αυτόματα τα UTF-8 Byte Order Marks (BOM) για να αποτρέψει την εμφάνιση ακαταλαβίστικων χαρακτήρων στο stream σας.

## Εγκατάσταση & Μεταγλώττιση

1. **Ορίστε τις διαδρομές σας:** Ανοίξτε το αρχείο `.c` και ενημερώστε τις παρακάτω γραμμές με τις διαδρομές για τα δικά σας αρχεία κειμένου. Θυμηθείτε να χρησιμοποιήσετε διπλή κάθετο (`\\`) για τις διαδρομές στα Windows: <br>
    `const char* INPUT_FILE = "C:\\Path\\To\\Your\\Player_Output.txt";` <br>
    `const char* OUTPUT_FILE = "C:\\Path\\To\\Your\\Broadcaster_Input.txt";`

2. **Μεταγλώττιση (Compilation):** Μπορείτε να το κάνετε compile χρησιμοποιώντας οποιονδήποτε standard compiler της C για Windows (όπως το [Dev-C++](https://sourceforge.net/projects/orwelldevcpp/)). Επειδή πρόκειται για εφαρμογή με Γραφικό Περιβάλλον (GUI) που χρησιμοποιεί εγγενείς γραμματοσειρές και χρώματα των Windows, πρέπει να συμπεριλάβετε τις εξής εντολές στον linker:
    `-static-libgcc -mwindows`

3. **Εκτέλεση (Run):** Ανοίξτε το μεταγλωττισμένο .exe, ξεκινήστε το ραδιοφωνικό σας λογισμικό και το εργαλείο θα αναλάβει αθόρυβα τις μετατροπές στο παρασκήνιο!


# Radio-Greeklish-Converter-TXT-Files
A lightweight Windows GUI tool for web radio broadcasters. It automatically reads Greek song titles from a "Now Playing" TXT file, converts them to Greeklish, and outputs a clean file for streaming software like [BUTT](https://danielnoethen.de/butt/), solving all encoding issues

A lightweight, automated Windows desktop application written in C that solves the common text-encoding problem for Greek internet radio broadcasters. 

Many broadcasting tools (like [BUTT](https://danielnoethen.de/butt/)) struggle to correctly display UTF-8 Greek characters in the "Now Playing" stream metadata. This tool acts as a bridge: it reads the current track from your player's output text file (e.g., [AIMP](https://aimp.ru/) with [_Current Track Info to Any_](https://aimp.ru/?do=catalog&rec_id=358) extension), instantly converts the Greek characters to Greeklish (Latin alphabet), and writes the clean, stream-ready text to a new file.

**You can download the `.c`file [here](https://github.com/Konstantinos2106/Radio-Greeklish-Converter--TXT-Files-/raw/refs/heads/main/radio_greeklish.c)**

## Features
* **Smart Conversion Engine:** Accurately converts Greek characters to Latin, including diphthongs (ου, αυ, ει), accented characters, and cleans up floating accents.
* **Real-Time Monitoring:** Checks the input file every 2 seconds and updates the output file only when the song actually changes, saving disk I/O.
* **Modern Windows GUI:** Built with the native Win32 API, featuring a clean Dark Mode interface with Neon Blue highlights.
* **Zero CPU Footprint:** Extremely lightweight, meaning it won't interfere with your audio streaming software.
* **BOM Handling:** Automatically detects and skips UTF-8 Byte Order Marks to prevent gibberish characters in your stream.

## How to Setup & Compile

1. **Set your paths:** Open the `.c` file and update the following lines with the paths to your specific text files. Remember to use double backslashes (`\\`) for Windows paths: <br>
   `const char* INPUT_FILE = "C:\\Path\\To\\Your\\Player_Output.txt";` <br>
   `const char* OUTPUT_FILE = "C:\\Path\\To\\Your\\Broadcaster_Input.txt";`

2. **Compilation:** You can compile this using any standard C compiler for Windows (like [Dev-C++](https://sourceforge.net/projects/orwelldevcpp/)). Since this is a GUI application that uses native Windows fonts and colors, you must include the following linker flags:
`-static-libgcc -mwindows`

3. **Run:** Launch the compiled .exe, start your radio software, and the tool will silently handle the conversions in the background!
