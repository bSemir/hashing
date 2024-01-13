#include <iostream>

using namespace std;

// definicija klase OtvorenoAdr(otvoreno adresiranje)

template <class Tip>
class OtvorenoAdr {
private:
    OtvorenoAdr(const OtvorenoAdr &);             // zabrana kopiranja
    OtvorenoAdr &operator=(const OtvorenoAdr &);  // zabrana dodjele
protected:
    Tip *Elementi;
    Tip praznoMjesto;  // oznaka praznog mjesta
    int velicina;
    virtual int h(const Tip &k, int i) const = 0;  // hash function
public:
    OtvorenoAdr(Tip praznoMjesto, int velicina = 100);
    ~OtvorenoAdr();
    bool UmetniHash(const Tip &k);
    int TraziHash(const Tip &searchItem) const;
    void Prikazi();  // const?
};

// konstruktor
template <class Tip>
OtvorenoAdr<Tip>::OtvorenoAdr(Tip praznoMjesto, int velicina) {
    this->praznoMjesto = praznoMjesto;
    this->velicina = velicina;
    Elementi = new Tip[velicina];
    for (int i = 0; i < velicina; i++) {
        Elementi[i] = praznoMjesto;
    }
}

// destruktor
template <class Tip>
OtvorenoAdr<Tip>::~OtvorenoAdr() {
    delete[] Elementi;
}

// prikazi
template <class Tip>
void OtvorenoAdr<Tip>::Prikazi() {
    for (int i = 0; i < velicina; ++i) {
        cout << i << ": " << Elementi[i] << endl;
    }
}

// umetni
template <class Tip>
bool OtvorenoAdr<Tip>::UmetniHash(const Tip &k) {
    int i = 0, j;
    do {
        j = h(k, i);  // hashiraj k i metni u j
        if (Elementi[j] == praznoMjesto) {
            Elementi[j] = k;
            return true;
        } else  // ako je zauzeto mjesto na koje je hashirano, povecaj i i ponovi,
            // sto znaci da se ide na sljedecu adresu
            i++;
    } while (i != velicina);
    return false;
}

// trazi
template <class Tip>
int OtvorenoAdr<Tip>::TraziHash(const Tip &k) const {
    int i = 0, j;
    do {
        j = h(k, i);  // adresa na kojoj bi se k trebao nalaziti
        if (Elementi[j] == k) {
            return j;
        } else
            i++;
    } while (Elementi[j] != praznoMjesto && i != velicina);
    return -1;
}

// definicija klase LinearniHash
template <class Tip>
class LinearniHash : public OtvorenoAdr<Tip> {
private:
    int h(const Tip &k, int i) const {
        return (k % this->velicina + i) % this->velicina;
    };

public:
    LinearniHash(Tip praznoMjesto = -1, int velicina = 10)
            : OtvorenoAdr<Tip>(praznoMjesto, velicina){};
};

// definicija klase DvostrukiHash
template <class Tip>
class DvostrukiHash : public OtvorenoAdr<Tip> {
private:
    int h(const Tip &k, int i) const { return (k % 13 + i * (k % 11 + 1)) % 13; }

public:
    DvostrukiHash(Tip praznoMjesto = -1, int velicina = 13)
            : OtvorenoAdr<Tip>(praznoMjesto, velicina){};
};

int Menu() {
    // Tabela T1 ima velicinu 10 - linearno hesiranje
    // Tabela T2 ima velicinu 13 - dvostruko hesiranje
    int izbor;
    cout << "\n-----Menu-----\n\n";
    cout << "1. Umetanje elemenata u tabelu T1\n";
    cout << "2. Pretrazivanje elemenata u tabeli T1\n";
    cout << "3. Prikaz sadrzaja tabele T1\n";
    cout << "---------------------------------\n";
    cout << "4. Umetanje elemenata u tabelu T2\n";
    cout << "5. Pretrazivanje elemenata u tabeli T2\n";
    cout << "6. Prikaz sadrzaja tabele T2\n";
    cout << "0. Izlaz\n\n";
    cout << "---Izaberite opciju---\n";
    cin >> izbor;
    if (cin)
        return izbor;
    else {
        cin.clear();
        cin.ignore(100, '\n');
        return -1;
    }
}

int main() {
    // OtvorenoAdr<int> *hash = new OtvorenoAdr<int>(-1, 10);
    // ne moze se napraviti objekt apstraktne klase OtvorenoAdr jer ima cistu virtuelnu funkciju
    const int praznoMjesto(-1);
    LinearniHash T1(praznoMjesto, 10);
    // LinearniHash<int> T1(praznoMjesto, 10);
    DvostrukiHash T2(praznoMjesto, 13);
    int x, p, izbor;
    while (izbor = Menu()) {
        try {
            switch (izbor) {
                case 0:
                    return 0;
                case 1:
                    cout << "\nUpisite cjelobrojnu vrijednost za unos u T1: ";
                    cin >> x;
                    if (T1.UmetniHash(x))
                        cout << "\nElementi je pohranjen u T1.\n";
                    else
                        cout << "\nElement nije pohranjen u T1.\n";
                    break;
                case 2:
                    cout << "\nUnesite broj kojeg pretrazujemo u T1:";
                    cin >> x;
                    p = T1.TraziHash(x);
                    if (p != praznoMjesto)
                        cout << "\nElement " << x << " je pronadjen,i=" << p << endl;
                    else
                        cout << "\nElement nije pronaden u T1.\n";
                    break;
                case 3:
                    cout << "\nSadrzaj hes-tabele T1:\n" << endl;
                    T1.Prikazi();
                    break;
                case 4:
                    cout << "\nUpisite cjelobrojnu vrijednost za unos u T2: ";
                    cin >> x;
                    if (T2.UmetniHash(x))
                        cout << "\nElementi je pohranjen u T2.\n";
                    else
                        cout << "\nElement nije pohranjen u T2.\n";
                    break;
                case 5:
                    cout << "\nUnesite broj kojeg pretrazujemo u T2:";
                    cin >> x;
                    p = T2.TraziHash(x);
                    if (p != praznoMjesto)
                        cout << "\nElement " << x << " je pronadjen,i=" << p << endl;
                    else
                        cout << "\nElement nije pronaden u T2.\n";
                    break;
                case 6:
                    cout << "\nSadrzaj hes-tabele T2:\n" << endl;
                    T2.Prikazi();
                    break;
                default:
                    cout << "\nPogresan izbor. Ponovite izbor!\n";
                    break;
            }
        } catch (const char greska[]) {
            cout << greska;
        } catch (...) {
            cout << "\nGreska u programu";
        }
    }
}