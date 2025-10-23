#include <stdio.h>     // Librería estándar para entrada/salida (printf, scanf)
#include <stdlib.h>    // Librería estándar para malloc, realloc, free

int main() {

    // Puntero dinámico donde se guardarán las calificaciones.
    float *calificaciones = NULL;

    // Contador del total de calificaciones almacenadas hasta ahora.
    int total_calificaciones = 0;

    // Variable para almacenar la opción del menú.
    int opcion_menu;

    // Bucle principal del programa: se repite mientras no se elija la opción 2 (salir).
    do {

        // Mostrar el menú principal
        printf("\n--- Menú Principal ---\n");
        printf("1) Ingresar calificaciones\n");
        printf("2) Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion_menu); // Leer la opción que el usuario elige


        // Si el usuario eligió ingresar calificaciones
        if (opcion_menu == 1) {
            char agregar_mas; // Variable para preguntar si desea agregar más al final

            // Este do-while permite agregar más calificaciones sin volver al menú
            do {
                int nuevas; // Número de nuevas calificaciones que desea ingresar

                printf("\n¿Cuántas calificaciones desea ingresar?: ");
                scanf("%d", &nuevas); // Leer ese número

                // Calculamos el nuevo total de calificaciones (anteriores + nuevas)
                int nuevo_total = total_calificaciones + nuevas;

                // realloc amplía (o crea, si NULL) el bloque de memoria para guardar más calificaciones
                calificaciones = realloc(calificaciones, nuevo_total * sizeof(float));

                // Validar que la asignación de memoria haya sido exitosa
                if (calificaciones == NULL) {
                    printf("Error: No se pudo asignar memoria.\n");
                    return 1; // Terminar programa con error
                }

                // Solicitar las nuevas calificaciones y validarlas entre 0 y 10
                printf("Ingrese las %d calificaciones (de 0 a 10):\n", nuevas);
                for (int i = total_calificaciones; i < nuevo_total; i++) {
                    float calif_temp; // variable temporal para leer cada calificación

                    do {
                        printf("Calificación %d: ", i + 1);
                        scanf("%f", &calif_temp); // leer una calificación

                        // Validación: si está fuera de rango, se repite
                        if (calif_temp < 0.0f || calif_temp > 10.0f) {
                            printf("Error: Calificación fuera de rango. Intente de nuevo.\n");
                        }

                    } while (calif_temp < 0.0f || calif_temp > 10.0f);

                    // Si es válida, la guardamos en el arreglo dinámico
                    calificaciones[i] = calif_temp;
                }

                // Actualizar el total de calificaciones registradas
                total_calificaciones = nuevo_total;

                // Calcular la suma y el promedio general de todas las calificaciones guardadas
                float suma = 0.0f;
                for (int i = 0; i < total_calificaciones; i++) {
                    suma += calificaciones[i];
                }
                float promedio = suma / total_calificaciones;

                // Mostrar resultados
                printf("\n--- Resultados ---\n");
                printf("Promedio general: %.2f\n", promedio);
                printf("Estado: %s\n", (promedio >= 7.0) ? "APROBÓ" : "REPROBÓ");

                // Preguntar si desea seguir agregando calificaciones
                printf("\n¿Desea agregar más calificaciones? (s/n): ");
                scanf(" %c", &agregar_mas); // Espacio antes de %c evita leer el salto de línea anterior

            } while (agregar_mas == 's'); // Repite mientras el usuario escriba 's'
        }

    } while (opcion_menu != 2); // Vuelve al menú principal si no eligió salir


    // Liberar la memoria dinámica antes de cerrar el programa
    free(calificaciones);
    printf("\nMemoria liberada. ¡Adiós! \n");

    return 0; // Fin del programa correctamente
}

