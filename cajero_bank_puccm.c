#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// ----- ESTAS FUNCIONES SON MIAS ------------//

void imprimirMenu();
// ----- DE AQUI PARA ABAJO ESTAS FUNCIONES NO SON MIAS ------------//

int clientesAtiendeCajero(int size, int clientesCajero[3][size], int cajero);
long atenderClienteCajero(int size, int clientesCajero[3][size], int codigoCajero);
long generarNumeroTicket(int size, int clientesCajero[3][size]);
void listarClientesEnCola(int size, int clientesCajero[3][size]);

// aqui  comienzo  a desarrollar el sistema//
int main()
{

    int opcion;// cosa del bucle
    int size;
    int cajero;
    int clientes;

    printf("************************* BANK PUCCM SRL *************************\n");



    printf(" Introduzca la cantidad de clientes a procesar : ");
    scanf("%d",&size);


    int clientesCajero[3][size];
    memset(clientesCajero,0,sizeof(clientesCajero));
    system("cls");
    do
    {

        imprimirMenu();
        printf("\nSeleccionar Opci%cn : ",162);
        scanf("%d",&opcion);



        switch(opcion)
        {

        case 1:
        {

            long ticket = generarNumeroTicket(size,clientesCajero);

            if (ticket == -1)
            {
                printf("\nLo siento, todos los cajero estan llenos, parece en la sombrita yo lo llamo cuando alla un ticket libre....\n");
            }
            else
            {
                printf("\nSu No. Ticket Es : %ld y ser%c atendido por el cajero no. %ld !",ticket,160,(ticket - 1) % 3 + 1); // esto % 3 + 1 es para que se le otorgue al cajero que sigue y esto (ticket - 1) es por que el ticket comienza en 1 y los cajero son 0 1 , que en  alguin que no sepa matris sera 1 2 3 cajero//
            }


            break;
        }

        case 2:
        {


            printf("Ingrese el n%cmero Del Cajero Que Desea Atender : ",163 );
            scanf("%d",&cajero);



            if(cajero < 1 || cajero > 3)
            {
                printf("\nLo Siento Solo Existe 3 Cajeros Por Ahora !!!!");
            }
            else
            {
                 long ticketAtendido = atenderClienteCajero(size, clientesCajero, cajero - 1); // aqui tenia un error y estaba llamando la funcion clientesAtiendeCajero//
                if( ticketAtendido == 0 ){

                    printf("\nLo siento, creo que tendras que ir al medico, por que en el cajero %d no hay clientes en fila",cajero);

                } else {

                    printf("\nTicket %ld Fue A tendido Exitosamente por el Cajero %ld !",ticketAtendido, cajero);

                }

            }

        }

        break;

        case 3:

            printf("\n%-9s %24s", "Cajeros", "Tickets en cola");
            printf("\n--------------------------------------------------\n");
            for (int g = 0; g < 3; g++)
            {
                printf("%-3d %19d\n", g + 1 ,clientesAtiendeCajero(size, clientesCajero, g));// aqui tuve un error que era que en ves de tener a g tenia disque cajero//
            }
            printf("--------------------------------------------------\n");
            break;

        case 4:


            listarClientesEnCola(size,clientesCajero);

            break;

        case 5:

            printf("\nGracias por Usar BANK PUCCM SRL, FELIZ RESTO DEL D%ca\n",161);

            break;

        default:
            printf("\nLa opcion que ingreso es invalida !!!");
        }

        printf("\n\n");
        printf("Para Continuar Preciones una Tecla ...");
        fflush(stdin);
        getchar();
        system("cls"); 
    }
    while(opcion != 5);

    return 0;
}

void imprimirMenu()
{
    
     printf("************************* BANK PUCCM SRL *************************\n");
    printf("\n1. Generar Ticket");
    printf("\n2. Atender Cliente");
    printf("\n3. Consultar Cantidad Cliente Cajero");
    printf("\n4. Listar Cliente En Cola");
    printf("\n5. Salir");

}

int clientesAtiendeCajero(int size, int clientesCajero[3][size], int cajero)
{
    int contadorDeCajero = 0;
    for (int g = 0; g < size; g++)
    {
        if (clientesCajero[cajero][g] != 0)
        {
            contadorDeCajero++;
        }
    }
    return contadorDeCajero;
}

long atenderClienteCajero(int size, int clientesCajero[3][size], int codigoCajero)
{
    for (int g = 0; g < size; g++)
    {
        if (clientesCajero[codigoCajero][g] != 0)
        {
            long ticketAtendido = clientesCajero[codigoCajero][g];
            for (int t = g; t < size - 1; t++)
            {
                clientesCajero[codigoCajero][t] = clientesCajero[codigoCajero][t + 1];
            }
            clientesCajero[codigoCajero][size - 1] = 0;

            return ticketAtendido;
        }
    }

    return 0;

}

long generarNumeroTicket(int size, int clientesCajero[3][size])
{
    static long contadorTicket = 1;  
    int minCajero = -1, minClientes = size;

    
    for (int g = 0; g < 3; g++)
    {
        int clientesEnCola = clientesAtiendeCajero(size, clientesCajero, g);

        if (clientesEnCola < size && clientesEnCola < minClientes)
        {
            minClientes = clientesEnCola;
            minCajero = g;
        }
    }

     if(minCajero == -1) 
    {
        return -1;
    }

    

    for (int t = 0; t < size; t++)
    {
        if (clientesCajero[minCajero][t] == 0)
        {
            clientesCajero[minCajero][t] = contadorTicket;
            return contadorTicket++;

        }
    }


}


void listarClientesEnCola(int size, int clientesCajero[3][size])
{
    printf("\n%-9s %24s", "Cajeros", "Tickets en cola");
    printf("\n--------------------------------------------------\n");

    for (int g = 0; g < 3; g++)
    {
        printf("%-9d",g + 1);
        int hayClienteEnFila = 0;

        for (int t = 0; t < size; t++)
        { if(clientesCajero[g][t] != 0){

            printf("%10d",clientesCajero[g][t]);
            hayClienteEnFila = 1;
        }

        }
        printf("\n");
    }
    printf("--------------------------------------------------\n");
}










