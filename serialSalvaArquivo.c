#include <windows.h>
#include <stdio.h>
#include <time.h>  // Adicionado para usar as fun��es relacionadas ao tempo
#include <unistd.h>  // Adicionado para usar a fun��o sleep

int main() {
    HANDLE hSerial;
    DCB dcbSerialParams = {0};
    COMMTIMEOUTS timeouts = {0};
    FILE *arquivo;

    // Abre a porta serial
    hSerial = CreateFile("COM4", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hSerial == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Erro ao abrir a porta serial\n");
        return 1;
    }

    // Configura��es da porta serial
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(hSerial, &dcbSerialParams)) {
        fprintf(stderr, "Erro ao obter as configura��es da porta serial\n");
        CloseHandle(hSerial);
        return 1;
    }

    dcbSerialParams.BaudRate = CBR_9600;  // Velocidade da porta serial (ajuste conforme necess�rio)
    dcbSerialParams.ByteSize = 8;         // Tamanho do byte
    dcbSerialParams.StopBits = ONESTOPBIT; // Um bit de parada
    dcbSerialParams.Parity   = NOPARITY;   // Sem paridade

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        fprintf(stderr, "Erro ao configurar a porta serial\n");
        CloseHandle(hSerial);
        return 1;
    }

    // Configura��o do timeout
    timeouts.ReadIntervalTimeout         = 50;
    timeouts.ReadTotalTimeoutConstant    = 50;
    timeouts.ReadTotalTimeoutMultiplier  = 10;
    timeouts.WriteTotalTimeoutConstant   = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(hSerial, &timeouts)) {
        fprintf(stderr, "Erro ao configurar timeouts\n");
        CloseHandle(hSerial);
        return 1;
    }

    // Leitura e impress�o dos dados
    char buffer[100];  // Tamanho do buffer ajust�vel conforme necess�rio
    DWORD bytesRead;

    while (1) {
        arquivo = fopen("saida.txt", "a");
        if (arquivo == NULL) {
            fprintf(stderr, "Erro ao abrir o arquivo\n");
            return 1;
        }

        // Obt�m a data e hora atual
        time_t tempo_atual;
        struct tm *info_tempo;
        time(&tempo_atual);
        info_tempo = localtime(&tempo_atual);

        if (ReadFile(hSerial, buffer, sizeof(buffer), &bytesRead, NULL)) {
    if (bytesRead > 0) {
        // Substitui qualquer caractere de nova linha ou retorno de carro por um espa�o em branco
        for (DWORD i = 0; i < bytesRead; ++i) {
            if (buffer[i] == '\n' || buffer[i] == '\r' || buffer[i] == ' ') {
                buffer[i] = ' ';
            }
        }

        printf("%.*s- %04d-%02d-%02d %02d:%02d:%02d\n",
                bytesRead,
                buffer,
                info_tempo->tm_year + 1900,
                info_tempo->tm_mon + 1,
                info_tempo->tm_mday,
                info_tempo->tm_hour,
                info_tempo->tm_min,
                info_tempo->tm_sec);

        fprintf(arquivo,"%.*s - %04d-%02d-%02d %02d:%02d:%02d\n",
                bytesRead,
                buffer,
                info_tempo->tm_year + 1900,
                info_tempo->tm_mon + 1,
                info_tempo->tm_mday,
                info_tempo->tm_hour,
                info_tempo->tm_min,
                info_tempo->tm_sec);

        fclose(arquivo);

    }
} else {
            fprintf(stderr, "Erro na leitura da porta serial\n");
            fclose(arquivo);  // Adicionado para fechar o arquivo em caso de erro
            break;
        }
    }

    // Fecha a porta serial
    CloseHandle(hSerial);

    return 0;
}
