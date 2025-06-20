#include <iostream>                                          // Libreria per input/output da console
#include <fstream>                                           // Libreria per input/output da file
#include <queue>                                             // Libreria per la priority_queue
#include <unordered_map>                                     // Mappa hash per frequenze e codici
#include <string>                                            // Per usare stringhe

using namespace std;                                         // Usa lo spazio dei nomi standard

// Nodo dell'albero di Huffman
struct HuffmanNode {
    char ch;                                                 // Carattere rappresentato (solo per foglie)
    int freq;                                                // Frequenza totale (per foglie o nodi interni)
    HuffmanNode *left, *right;                               // Puntatori ai figli sinistro e destro
    HuffmanNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {} // Costruttore
};

// Comparatore per la priority_queue (min-heap)
struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq;                            // Restituisce true se a ha frequenza maggiore di b
    }
};

// Costruisce l'albero di Huffman
// @param freqMap - Mappa dei caratteri con le rispettive frequenze
// @return Puntatore alla radice dell'albero di Huffman
HuffmanNode* buildHuffmanTree(unordered_map<char, int>& freqMap) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;  // Coda di priorità con comparatore
                                //vector<HuffmanNode*> e' la struttura che verra' usata per implementare la queue

    for (auto& pair : freqMap)                               // Crea un nodo per ogni carattere
        pq.push(new HuffmanNode(pair.first, pair.second));

    while (pq.size() > 1) {                                  // Combina i nodi più piccoli finché ne rimane uno
        HuffmanNode* left = pq.top(); pq.pop();              // Nodo con frequenza minore
        HuffmanNode* right = pq.top(); pq.pop();             // Secondo nodo con frequenza minore
        HuffmanNode* merged = new HuffmanNode('\0', left->freq + right->freq); // Nodo interno
        merged->left = left;                                 // Assegna il figlio sinistro
        merged->right = right;                               // Assegna il figlio destro
        pq.push(merged);                                     // Inserisci nodo interno nella coda
    }

    return pq.top();                                         // Radice dell'albero di Huffman
}

// Genera i codici binari per ciascun carattere tramite visita DFS dell'albero
// @param root - Radice dell'albero di Huffman
// @param code - Codice binario costruito finora
// @param huffmanCode - Mappa dei caratteri con il loro codice Huffman
void generateCodes(HuffmanNode* root, string code, unordered_map<char, string>& huffmanCode) {
    if (!root)
        return;                                       // Nodo nullo, ritorna

    if (!root->left && !root->right)                         // Se è una foglia
        huffmanCode[root->ch] = code;                        // Salva il codice nella mappa

    generateCodes(root->left, code + "0", huffmanCode);      // Aggiungi '0' e visita figlio sinistro
    generateCodes(root->right, code + "1", huffmanCode);     // Aggiungi '1' e visita figlio destro
}

// Codifica il testo usando i codici Huffman
// @param text - Stringa originale da codificare
// @param huffmanCode - Mappa dei caratteri con i rispettivi codici binari
// @return Stringa binaria codificata
string encode(const string& text, unordered_map<char, string>& huffmanCode) {
    string encodedText;
    for (char ch : text)                                     // Per ogni carattere nel testo
        encodedText += huffmanCode[ch];                      // Aggiungi il codice Huffman
    return encodedText;
}

// Decodifica una stringa binaria usando l'albero di Huffman
// @param root - Radice dell'albero Huffman
// @param encodedText - Stringa codificata da decodificare
// @return Testo originale decodificato
string decode(HuffmanNode* root, const string& encodedText) {
    string decodedText;
    HuffmanNode* current = root;

    for (char bit : encodedText) {                           // Per ogni bit nella stringa codificata
        if (bit == '0')
            current = current->left;                         // Vai a sinistra
        else
            current = current->right;                        // Vai a destra

        if (!current->left && !current->right) {             // Se è una foglia
            decodedText += current->ch;                      // Aggiungi il carattere decodificato
            current = root;                                  // Riparti dalla radice
        }
    }
    return decodedText;
}

int main() {
    string filename = "input.txt";                           // Nome del file da cui leggere il testo
    ifstream inputFile(filename);                            // Apri il file in lettura

    if (!inputFile) {                                        // Verifica apertura file
        cerr << "Errore nell'apertura del file: " << filename << '\n';
        return 1;
    }

    string text((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>()); // Legge tutto il contenuto
    inputFile.close();                                       // Chiudi il file

    if (text.empty()) {                                      // Verifica se il file è vuoto
        cerr << "Il file è vuoto.\n";
        return 1;
    }

    unordered_map<char, int> freqMap;
    for (char ch : text)                                     // Conta la frequenza di ogni carattere
        freqMap[ch]++;

    HuffmanNode* root = buildHuffmanTree(freqMap);           // Costruisce l'albero di Huffman
    unordered_map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode);                    // Genera i codici per ogni carattere

    cout << "\nCodici di Huffman:\n";
    for (auto& pair : huffmanCode)
        cout << pair.first << " : " << pair.second << '\n';  // Stampa i codici Huffman

    string encoded = encode(text, huffmanCode);              // Codifica il testo
    cout << "\nTesto codificato:\n" << encoded << '\n';

    string decoded = decode(root, encoded);                  // Decodifica il testo
    cout << "\nTesto decodificato:\n" << decoded << '\n';

    // ✅ Salva la codifica su encoded.txt
    ofstream encodedFile("encoded.txt");
    if (!encodedFile) {
        cerr << "Errore nella scrittura di encoded.txt\n";
        return 1;
    }
    encodedFile << encoded;                                  // Scrivi il testo codificato
    encodedFile.close();
    cout << "\nIl testo codificato è stato scritto in encoded.txt\n";

    // ✅ Salva la decodifica su decoded.txt
    ofstream decodedFile("decoded.txt");
    if (!decodedFile) {
        cerr << "Errore nella scrittura di decoded.txt\n";
        return 1;
    }
    decodedFile << decoded;                                  // Scrivi il testo decodificato
    decodedFile.close();
    cout << "Il testo decodificato è stato scritto in decoded.txt\n";

    return 0;
}