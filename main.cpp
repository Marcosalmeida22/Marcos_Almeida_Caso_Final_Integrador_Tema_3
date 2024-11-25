//
// Created by malme on 23/11/2024.
//

#include "main.h"
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

struct ColorConsole
{
    static constexpr auto fg_blue = "\033[34m";
    static constexpr auto bg_white = "\033[47m";
};

struct ConsoleBox
{
    void new_text() { /* ... */ }
    void set_text(const string &text) { cout << text << endl; }
};

ConsoleBox *consoleBox = new ConsoleBox; // suponemos que ya está inicializado

void load_script(const char *filename, bool show_script = false) {
    string script;
    FILE *f = nullptr;

    // Intentar abrir el archivo
    f = fopen(filename, "rb");
    if (!f)
    {
        cerr << "Error: No se pudo abrir el archivo " << filename << endl;
        return;
    }

    try
    {
        // Leer el contenido del archivo
        char buf[4001];
        size_t bytes_read;
        while ((bytes_read = fread(buf, 1, 4000, f)) > 0)
        {
            buf[bytes_read] = '\0';
            script.append(buf);
        }

        // Verificar errores de lectura
        if (ferror(f))
        {
            throw runtime_error("Error al leer el archivo.");
        }

        // Mostrar el script si es necesario
        if (show_script)
        {
            cout << ColorConsole::fg_blue << ColorConsole::bg_white;
            cout << script << endl;
        }

        // Usar el script en ConsoleBox
        consoleBox->new_text();
        consoleBox->set_text(script);

        // Cerrar el archivo
        fclose(f);
        f = nullptr;
    }
    catch (const exception &e)
    {
        cerr << "Excepción: " << e.what() << endl;
        if (f)
            fclose(f);
    }
    catch (...)
    {
        cerr << "Error inesperado durante la lectura del archivo." << endl;
        if (f)
            fclose(f);
    }
}

void load_script()
{
    char filename[500];
    printf("Archivo: ");
    if (scanf("%499s", filename) != 1)
    {
        cerr << "Error al leer el nombre del archivo." << endl;
        return;
    }

    load_script(filename, true);
}

int main()
{
    load_script("script.txt");
    load_script();
    return 0;
}