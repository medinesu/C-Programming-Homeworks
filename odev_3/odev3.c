
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

typedef struct Node Node;
Node* head = NULL;

void yazdir();
void ekleBasa(int veri);
void arayaEkle(int veri, int pozisyon);
void ekleSona(int veri);
void siraIleSil(); 

int main() {
    int secim, veri, poz;

    while (1) {
        printf("\n--- MENU ---\n");
        printf("1. Basa Ekle\n");
        printf("2. Araya Ekle\n");
        printf("3. Sona Ekle\n");
        printf("4. Yazdir\n");
        printf("5. Çikis\n");
        printf("6. Sıraya Göre Sil (Pozisyon girerek)\n"); 
        printf("Seçiminizi yapın: ");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                printf("Eklenecek veri: ");
                scanf("%d", &veri);
                ekleBasa(veri);
                break;
            case 2:
                printf("Eklenecek veri: ");
                scanf("%d", &veri);
                printf("Pozisyon (0'dan baslar): ");
                scanf("%d", &poz);
                arayaEkle(veri, poz);
                break;
            case 3:
                printf("Eklenecek veri: ");
                scanf("%d", &veri);
                ekleSona(veri);
                break;
            case 4:
                yazdir();
                break;
            case 5:
                printf("Programdan çıkılıyor...\n");
                exit(0);
            case 6:
                siraIleSil(); 
                break;
            default:
                printf("Geçersiz seçim!\n");
        }
    }

    return 0;
}

void yazdir() {
    Node* temp = head;
    printf("Liste: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void ekleBasa(int veri) {
    Node* yeni = (Node*)malloc(sizeof(Node));
    yeni->data = veri;
    yeni->next = head;
    head = yeni;
}

void arayaEkle(int veri, int pozisyon) {
    Node* yeni = (Node*)malloc(sizeof(Node));
    yeni->data = veri;
    yeni->next = NULL;

    if (pozisyon == 0) {
        yeni->next = head;
        head = yeni;
        return;
    }

    Node* temp = head;
    for (int i = 0; i < pozisyon - 1; i++) {
        if (temp == NULL) {
            printf("Pozisyon listeden büyük! Ekleme yapilamadi.\n");
            free(yeni);
            return;
        }
        temp = temp->next;
    }

    yeni->next = temp->next;
    temp->next = yeni;
}

void ekleSona(int veri) {
    Node* yeni = (Node*)malloc(sizeof(Node));
    yeni->data = veri;
    yeni->next = NULL;

    if (head == NULL) {
        head = yeni;
        return;
    }

    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = yeni;
}

void siraIleSil() {
    if (head == NULL) {
        printf("Liste bos, silinecek bir sey yok.\n");
        return;
    }

    int position;
    printf("Kacinci siradaki dugum silinsin? (0'dan baslayarak girin): ");
    scanf("%d", &position);

    if (position < 0) {
        printf("Gecersiz pozisyon!\n");
        return;
    }

    Node *temp = head;

    
    if (position == 0) {
        head = temp->next;
        printf("Silinen veri: %d\n", temp->data);
        free(temp);
        return;
    }

    
    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) {
        printf("Pozisyon liste uzunlugundan buyuk, silme islemi yapilamadi.\n");
        return;
    }

    Node *sil = temp->next;
    temp->next = sil->next;
    printf("Silinen veri: %d\n", sil->data);
    free(sil);
}


