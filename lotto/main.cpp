#include <stdio.h>
#include<windows.h>
#include <math.h>
#include "winbgi2.h"
#include <time.h>
#include <stdlib.h>
#include <cstdlib>

void initPosition(double T[49][5], int N);
void collideWall(double t[49][5], int N);
void move(double t[49][5], int N);
void display(double t[49][5], int N);
void collideBall(double t[49][5], int N);
void dmuchawalewa(double t[49][5], int n);
void dmuchawaprawa(double t[49][5], int n);
void sortuj(double t[49][5], int n);
void sortuj1(int t[6], int n);
void zasysanie(double t[49][5], int n, int w[6]);
void kula(double x, double y, int r);
void instrukcja();

int main()
{
    double K[49][5];
    int wynik[6] = { 0,0,0,0,0,0 };
    int numery[6] = { 0,0,0,0,0,0 };
    int n = 49;
    int suma = 0;
    int k = 0;
    int x = 0;
    int traf = 0;
    int stop = 0;
    srand(time(NULL));

    instrukcja();
    printf("Wpisz do konsoli numery 6 kul, ktore obstawiasz:\n");
    for (int i = 0; i < 6; i++)
    {
        scanf("%d", &numery[i]);
    }
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (i == j)break;
            if (numery[i] == numery[j])
            {
                printf("Numery nie moga sie powtarzac!\n");
                exit(0);
            }
        }
    }
    for (int i = 0; i < 6; i++)
    {
        if (numery[i] <= 0 || numery[i] > 49)
        {
            printf("Numery musza byc w zakresie od 1 do 49!\n");
            exit(0);
        }
    }
    printf("Oto Twoje numery: ");
    sortuj1(numery, 6);
    for (int r = 0; r < 6; r++)
    {
        printf("%d, ", numery[r]);
    }

    graphics(800, 800);
    initPosition(K, n);

    for (int j = 0; j < n; j++) K[j][4] = j + 1; //liczba losowana

    while (x == 0)
    {
        if (mouseup() == 1)x++;
    }
    if (x != 0)
    {
        while (stop < 2)
        {
            animate(100);
            clear();
            setgray(1);
            line(100, 100, 100, 700);
            line(100, 700, 700, 700);
            line(700, 700, 700, 100);
            line(700, 100, 100, 100);

            collideWall(K, n);
            collideBall(K, n);
            move(K, n);
            display(K, n);
            if (mouseup() == 1)
            {
                k++;
                // printf("dupa\tdupa\n");
            }
            if (k > 0)
            {
                dmuchawalewa(K, n);
                dmuchawaprawa(K, n);
            }
            if (k > 1)
            {
                zasysanie(K, n, wynik);
                for (int p = 0; p < n; p++)
                {
                    if (K[p][4] == 50) suma++;  //liczba losowana
                }
                if (suma != 0)
                {
                    n--;
                    k = 1;
                    suma = 0;
                }
            }
            for (int q = 0; q < 6; q++)
            {
                setcolor(2 * (double)wynik[q] / 100);

                if (wynik[q] != 0)
                {
                    kula(115 + (q * 40), 70, 15);
                    int nri;
                    char str[8];
                    nri = wynik[q];
                    if (wynik[q] < 10)
                    {
                        sprintf_s(str, "0%d", nri);
                        outtextxy(115 + (q * 40) - 9, 70 - 7, str);
                    }
                    else
                    {
                        sprintf_s(str, "%d", nri);
                        outtextxy(115 + (q * 40) - 9, 70 - 7, str);
                    }
                }
                else break;
                setgray(1);
            }
            if (wynik[5] != 0) stop++;
        }
    }
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (numery[i] == wynik[j]) traf++;
        }
    }
    printf("\nUdalo Ci sie trafic %d kul\n", traf);

    if (traf == 0)
    {
        printf("Sprobuj nastepnym razem\n ");
    }

    if (traf == 6)
    {
        printf("Gratulacje, trafiles szostke\n");
    }
    sortuj1(wynik, 6);
    printf("\nOto wyniki kumulacji: ");
    for (int r = 0; r < 6; r++)
    {
        printf("%d, ", wynik[r]);
    }
    wait();

    return 0;
}

void initPosition(double T[49][5], int N)
{
    int i;
    double pit;
    for (i = 0; i < N; i++)
    {
        T[i][0] = 115 + 570 * (double)rand() / RAND_MAX;
        T[i][1] = 115 + 570 * (double)rand() / RAND_MAX;
        T[i][2] = -1 + (2 * (double)rand() / RAND_MAX);
        T[i][3] = -1 + (2 * (double)rand() / RAND_MAX);
        for (int j = 0; j < i; j++)
        {
            pit = pow(T[i][0] - T[j][0], 2) + pow(T[i][1] - T[j][1], 2);
            if (pit < 900)
            {
                i--;
                break;
            }
        }
    }
}

void collideWall(double t[49][5], int N)
{
    for (int i = 0; i < N; i++)
    {
        if (t[i][0] < 115 || t[i][0]>685) t[i][2] = (-1) * t[i][2];
        if (t[i][1] < 115 || t[i][1]>685) t[i][3] = (-1) * t[i][3];
    }
}

void move(double t[49][5], int N)
{
    for (int i = 0; i < N; i++)
    {
        int crashedx[49] = { 0 };
        int crashedy[49] = { 0 };
        t[i][0] += t[i][2];
        t[i][1] += t[i][3];
        t[i][3] += 0.03; //GRAWITACJA
        for (int i = 0; i < N; i++)
        {
            if ((t[i][0] < 115) && (t[i][2] < 0)) {
                t[i][0] = 115 + 0.7 * t[i][2];
                crashedx[i] = 1;
            }
            else if ((t[i][1] < 115) && (t[i][3] < 0))
            {
                t[i][1] = 115 + 0.7 * t[i][3];
                crashedy[i] = 1;
            }
            else  if ((t[i][0] > 685) && (t[i][2] > 0))
            {
                t[i][0] = 685 + 0.7 * t[i][2];
                crashedx[i] = 2;
            }
            else if ((t[i][1] > 685) && (t[i][3] > 0))
            {
                t[i][1] = 685 + 0.7 * t[i][3];
                crashedy[i] = 2;
            }
        }
    }
}

void display(double t[49][5], int N)
{
    for (int i = 0; i < N; i++)
    {
        int nri;
        char str[8];
        setcolor(2 * t[i][4] / 100);
        circle(t[i][0], t[i][1], 15);
        setgray(1);
        nri = (int)t[i][4];
        if (t[i][4] < 10)
        {
            sprintf_s(str, "0%d", nri);
            outtextxy(t[i][0] - 9, t[i][1] - 7, str);
        }
        else
        {
            sprintf_s(str, "%d", nri);
            outtextxy(t[i][0] - 9, t[i][1] - 7, str);
        }
    }
}

void collideBall(double t[49][5], int N)
{
    double Cx, Cy, dxV, dyV, pit, pomoci, pomocj;
    double z[49] = { 0 };

    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            double rx, ry, cx, cy, dvx, dvy, L, srx, sry, kat, kat2;
            rx = t[i][0] - t[j][0];
            ry = t[i][1] - t[j][1];
            dvx = t[i][2] - t[j][2];
            dvy = t[i][3] - t[j][3];
            cx = (rx * dvx) / ((t[i][0] - t[j][0]) * (t[i][0] - t[j][0]));
            cy = (ry * dvy) / ((t[i][1] - t[j][1]) * (t[i][1] - t[j][1]));
            L = sqrt((t[i][0] - t[j][0]) * (t[i][0] - t[j][0]) + (t[i][1] - t[j][1]) * (t[i][1] - t[j][1]));
            if (L <= 30)
            {
                t[i][2] = t[i][2] - cx * rx;
                t[i][3] = t[i][3] - cy * ry;
                z[i]++;
                t[j][2] = t[j][2] + cx * rx;
                t[j][3] = t[j][3] + cy * ry;
                z[j]++;

                if (pow(t[i][2] - t[j][2], 2) < 0.01 && pow(t[i][3] - t[j][3], 2) < 0.01)
                {
                    printf("%d\t%d\n", i, j);
                }
                // srodek odcinka laczacego srodki kul 
                srx = (t[i][0] + t[j][0]) / 2;
                sry = (t[i][1] + t[j][1]) / 2;
                kat = fabs(t[i][1] - t[j][1]) / L; //sinus
                kat2 = fabs(t[i][0] - t[i][0]) / L;//cosinus

                if (t[i][0] < t[j][0] && t[i][1] < t[j][1])
                {
                    t[i][1] = sry - (16 * kat);
                    t[j][1] = sry + (16 * kat);
                }
                else if (t[i][0] > t[j][0] && t[i][1] < t[j][1])
                {
                    t[i][1] = sry - (16 * kat);
                    t[j][1] = sry + (16 * kat);
                }
                else if (t[i][0] > t[j][0] && t[i][1] > t[j][1])
                {
                    t[i][1] = sry + (16 * kat);
                    t[j][1] = sry - (16 * kat);
                }
                else if (t[i][0] < t[j][0] && t[i][1] > t[j][1])
                {
                    t[i][1] = sry + (16 * kat);
                    t[j][1] = sry - (16 * kat);
                }
            }
        }
    }
}

void dmuchawalewa(double t[49][5], int n)
{
    double Wx, Wy;
    double F = 0.7;
    double pit;
    for (int i = 0; i < n; i++)
    {
        pit = sqrt(pow(100 - t[i][0], 2) + pow(700 - t[i][1], 2));
        Wx = (1 - ((t[i][0] - 100) / 600)) * F / pit;
        Wy = (1 - ((t[i][1] - 100) / 600)) * F / pit;
        t[i][2] += Wx;
        t[i][3] -= Wy;
    }
}

void dmuchawaprawa(double t[49][5], int n)
{
    double Wx, Wy;
    double F = 0.7;
    double pit;
    for (int i = 0; i < n; i++)
    {
        pit = sqrt(pow(700 - t[i][0], 2) + pow(700 - t[i][1], 2));
        Wx = (1 - ((t[i][0] - 100) / 600)) * F / pit;
        Wy = (1 - ((t[i][1] - 100) / 600)) * F / pit;
        t[i][2] -= Wx;
        t[i][3] -= Wy;
    }
}

void sortuj(double t[49][5], int n)
{
    for (int i = 0, zmiany = 1; i < n - 1 && zmiany != 0; i++)
    {
        zmiany = 0;
        for (int j = 0; j < n - 1; j++)
        {
            if (t[j][4] > t[j + 1][4])
            {
                int pomoc = t[j][4]; //treba posortowa� wszyskie elementy tablicy
                t[j][4] = t[j + 1][4];//ZROBIONE
                t[j + 1][4] = pomoc;

                pomoc = t[j][3];
                t[j][3] = t[j + 1][3];
                t[j + 1][3] = pomoc;

                pomoc = t[j][2];
                t[j][2] = t[j + 1][2];
                t[j + 1][2] = pomoc;

                pomoc = t[j][1];
                t[j][1] = t[j + 1][1];
                t[j + 1][1] = pomoc;

                pomoc = t[j][0];
                t[j][0] = t[j + 1][0];
                t[j + 1][0] = pomoc;
                zmiany++;
            }
        }
    }
}

void sortuj1(int t[6], int n)
{
    for (int i = 0, zmiany = 1; i < n - 1 && zmiany != 0; i++)
    {
        zmiany = 0;
        for (int j = 0; j < n - 1; j++)
        {
            if (t[j] > t[j + 1])
            {
                int pomoc = t[j];
                t[j] = t[j + 1];
                t[j + 1] = pomoc;
                zmiany++;
            }
        }
    }
}

void zasysanie(double t[49][5], int n, int w[6])
{
    double Wx, Wy;
    double F = 3;
    double pit;
    for (int i = 0; i < n; i++)
    {
        pit = sqrt(pow(400 - t[i][0], 2) + pow(130 - t[i][1], 2));
        if (t[i][0] < 400) Wx = (1 - ((t[i][0] - 100) / 600)) * F / pit;
        else Wx = -(1 - ((t[i][0] - 100) / 600)) * F / pit;
        Wy = (1 - ((t[i][1] - 100) / 600)) * F / pit;
        t[i][2] += Wx;
        t[i][3] -= Wy;
        if (pit < 10)
        {
            Beep(400, 400);
            //printf("%lf", t[i][4]);
            for (int j = 0; j < 6; j++)
            {
                if (w[j] == 0)
                {
                    w[j] = t[i][4];
                    break;
                }
            }
            t[i][4] = 50;
        }
    }
    sortuj(t, n);
    circle(400, 130, 25);
    setgray(1);
}

void kula(double x, double y, int r)
{
    for (int i = r; i > 0; i--)
    {
        circle(x, y, i);
    }
}

void instrukcja()
{
    printf("       ___           __________     ____________     ____________    __________\n");
    printf("      /  /          /  _____  /    /____   ____/    /____   ____/   /  _____  / \n ");
    printf("    /  /          /  /    / /         /  /             /  /       /  /    / /\n");
    printf("    /  /          /  /    / /         /  /             /  /       /  /    / / \n ");
    printf("  /  /          /  /    / /         /  /             /  /       /  /    / /\n");
    printf("  /  /_____     /  /____/ /         /  /             /  /       /  /____/ /\n ");
    printf("/________/    /_________/         /__/             /__/       /_________/\n");
    printf("\n\n");
    printf("Instrukcja gry w LOTTO:\n\n");

    printf("1.Wypisz numery kul, ktore obstawiasz \n");
    printf("2.Aby zwolnic blokade maszyny losujacej przycisnij lewy przycisk myszy w polu graficznym. \n");
    printf("3.W celu uruchomienia dmuchaw w maszynie kliknij ponownie lewy przycisk myszy\n");
    printf("4.W celu zassania kazdej kolejnej kuli ponownie kliknij lewy przycisk myszy \n");
    printf("5.Po wylosowaniu 6 kul wyniki oraz ilosc trafionych numerow pokaza sie w konsoli\n\n");
}