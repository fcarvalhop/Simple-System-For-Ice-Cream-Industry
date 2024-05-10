#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

void Selecao();
void Busca();
void RegistroProduto();
void RegistroEstoque();
void RegistroFabricacao();
void RegistroVenda();
void BuscaFabricacaoData();
void BuscaVendaData();
void Imprimir();
void ImprimirFabricacao();
void ImprimirProduto();
void ImprimirVenda();

typedef struct produto
{
    char sabor[20];
    float valor;

} produto;

typedef struct data
{
    int dia;
    int mes;
    int ano;
} data;

typedef struct venda
{
    produto sorvet;
    data vendida;
    int vendas;

} venda;

typedef struct fabricacao
{
    produto sorvet;
    data fabricada;
    int fabricado;

} fabricacao;

void Selecao()
{
    int codigo = 9;
    while (codigo != 0)
    {

        fflush(stdin);
        printf("\nSelecione: ");
        printf("\n1 - Registrar sorvete; ");
        printf("\n2 - Registrar estoque; ");
        printf("\n3 - Consultas; ");
        printf("\n4 - Imprimir dados dos sorvetes; ");
        printf("\n0 - Sair\n");
        scanf("%d", &codigo);

        switch (codigo)
        {
            case 1:
                RegistroProduto();
                break;

            case 2:
                RegistroEstoque();
                break;

            case 3:
                Busca();
                break;

            case 4:
                Imprimir();
                break;

            case 0:
                printf("\nObrigado por utilizar o sistema de controle da Indústria de Sorvetes!\n");
                printf("\nSistema criado por Fernanda de Carvalho Pinto");
                exit(1);

            default:
                printf("\nCódigo incorreto, digite novamente.\n");
                break;
        }
    }
}

void Busca()
{
    int codigo = 9;
    while (codigo != 0)
    {

        fflush(stdin);
        printf("\nSelecione: ");
        printf("\n1 - Buscar fabricação por data; ");
        printf("\n2 - Buscar venda por data; ");
        printf("\n0 - Voltar ao menu principal\n");
        scanf("%d", &codigo);

        switch (codigo)
        {
            case 1:
                BuscaFabricacaoData();
                break;

            case 2:
                BuscaVendaData();
                break;

            case 0:
                Selecao();
                break;

            default:
                printf("\nCódigo incorreto, digite novamente.\n");
                break;
        }
    }
}

void RegistroProduto()
{
    FILE* pr;
    produto sorvete1;
    produto sorvete2;
    char continuar[] = "s";
    int j;

    while(strcmp(continuar, "n") != 0)
    {
        j = 0;
        fflush(stdin);
        printf("\nDigite o sabor do sorvete: ");
        gets(sorvete1.sabor);

        if ((pr = fopen("Industria_sorvete.bin", "rb")))
        {
            while(fread(&sorvete2, sizeof(struct produto), 1, pr))
            {
                if (strcmp(sorvete1.sabor, sorvete2.sabor) == 0)
                {
                    printf("\nSabor de sorvete já registrado.\n");
                    fflush(stdin);
                    j = 1;
                    printf("\nDeseja registrar outro sorvete? s/n\n");
                    gets(continuar);
                }
            }
            fclose(pr);
        }

        if (j == 0)
        {
            printf("\nDigite o valor de venda do sorvete: ");
            scanf("%f", &sorvete1.valor);
            fflush(stdin);

            pr = fopen("Industria_sorvete.bin", "ab");
            if(pr == NULL)
            {
                printf("\nNão foi possível abrir o arquivo");
                exit(1);
            }

            fwrite(&sorvete1 , sizeof (struct produto), 1, pr);

            fclose(pr);

            printf("\nDeseja registrar outro sorvete? s/n\n");
            gets(continuar);
        }

    }
}

void RegistroEstoque()
{
    int codigo = 9;
    while (codigo != 0)
    {
        fflush(stdin);
        printf("\nSelecione: ");
        printf("\n1 - Registrar fabricação; ");
        printf("\n2 - Registrar venda;");
        printf("\n0 - Voltar ao menu principal\n");
        scanf("%d", &codigo);

        switch (codigo)
        {
            case 1:
                RegistroFabricacao();
                break;

            case 2:
                RegistroVenda();
                break;

            case 0:
                Selecao();

            default:
                printf("\nCódigo incorreto, digite novamente.\n");
                break;
        }
    }
}

void RegistroFabricacao ()
{
    FILE* fb;
    fb = fopen("Fabricacao_sorvete.bin", "ab");

    if(fb == NULL)
    {
        puts("\nNão foi possível abrir o arquivo");
        exit(1);
    }

    FILE* pr;

    char continuar[] = "s";

    while(strcmp(continuar, "n") != 0)
    {
            fabricacao sorvete1;
            produto sorvete2;
            int j = 0;

            char sorvete[20];
            fflush(stdin);
            printf("\nDigite o sabor de sorvete fabricado: ");
            gets(sorvete);

            pr = fopen("Industria_sorvete.bin", "rb");

            if(pr == NULL)
            {
                puts("\nNão foi possível abrir o arquivo");
                exit(1);
            }

            while(fread(&sorvete2, sizeof(struct produto), 1, pr))
            {
                if ( strcmp(sorvete, sorvete2.sabor) == 0 )
                {
                    strcpy(sorvete1.sorvet.sabor, sorvete2.sabor);
                    sorvete1.sorvet.valor = sorvete2.valor;
                    j = 1;
                }
            }
            fclose(pr);

            if (j == 1)
            {
                fflush(stdin);
                printf("\nEntre a data da fabricação:");
                printf("\nDia da fabricação: ");
                scanf("%d", &sorvete1.fabricada.dia);


                fflush(stdin);
                printf("\nMês da fabricação (1 a 12):");
                scanf("%d", &sorvete1.fabricada.mes);

                fflush(stdin);
                printf("\nAno da fabricação: ");
                scanf("%d", &sorvete1.fabricada.ano);

                fflush(stdin);
                printf("\nQuantidade fabricada: ");
                scanf("%d", &sorvete1.fabricado);

                fwrite(&sorvete1 , sizeof (struct fabricacao), 1, fb);

                fflush(stdin);
                printf("\nDeseja registrar outra fabricação de sorvete? s/n\n");
                gets(continuar);
            }

            if (j == 0)
            {
                printf("\nSabor %s de sorvete não encontrado.\n", sorvete);

                fflush(stdin);
                printf("\nDeseja registrar outra fabricação de sorvete? s/n\n");
                gets(continuar);
            }
    }
    fclose(fb);
}

void RegistroVenda ()
{
    FILE* vd;
    vd = fopen("Venda_sorvete.bin", "ab");

    if(vd == NULL)
    {
        puts("\nNão foi possível abrir o arquivo");
        exit(1);
    }

    FILE* pr;

    char continuar[] = "s";

    while(strcmp(continuar, "n") != 0)
    {
            fflush(stdin);
            venda sorvete1;
            produto sorvete2;
            int j = 0;

            char sorvete[20];
            fflush(stdin);
            printf("\nDigite o sabor de sorvete vendido: ");
            gets(sorvete);

            pr = fopen("Industria_sorvete.bin", "rb");

            if(pr == NULL)
            {
                puts("\nNão foi possível abrir o arquivo");
                exit(1);
            }

            while(fread(&sorvete2, sizeof(struct produto), 1, pr) == 1)
            {
                if (strcmp(sorvete, sorvete2.sabor) == 0)
                {
                    strcpy(sorvete1.sorvet.sabor, sorvete2.sabor);
                    sorvete1.sorvet.valor = sorvete2.valor;
                    j = 1;
                }
            }
            fclose(pr);

            if (j == 1)
            {
                fflush(stdin);
                printf("\nEntre a data da venda:");
                printf("\nDia da venda: ");
                scanf("%d", &sorvete1.vendida.dia);


                fflush(stdin);
                printf("\nMês da venda (1 a 12):");
                scanf("%d", &sorvete1.vendida.mes);

                fflush(stdin);
                printf("\nAno da venda: ");
                scanf("%d", &sorvete1.vendida.ano);

                fflush(stdin);
                printf("\nQuantidade vendida: ");
                scanf("%d", &sorvete1.vendas);

                fwrite(&sorvete1 , sizeof (struct venda), 1, vd);

                fflush(stdin);
                printf("\nDeseja registrar outra venda de sorvete? s/n\n");
                gets(continuar);
            }

            if (j == 0)
            {
                printf("\nSabor %s de sorvete não encontrado.\n", sorvete);

                fflush(stdin);
                printf("\nDeseja registrar outra venda de sorvete? s/n\n");
                gets(continuar);
            }

    }
    fclose(vd);
}

void Imprimir()
{
    int codigo = 9;
    while (codigo != 0)
    {
        fflush(stdin);
        printf("\nSelecione: ");
        printf("\n1 - Imprimir todos os sabores de sorvete; ");
        printf("\n2 - Imprimir todas as fabricações; ");
        printf("\n3 - Imprimir todas as vendas; ");
        printf("\n0 - Voltar ao menu principal\n");
        scanf("%d", &codigo);

        switch (codigo)
        {
            case 1:
                ImprimirProduto();
                break;

            case 2:
                ImprimirFabricacao();
                break;

            case 3:
                ImprimirVenda();
                break;

            case 0:
                Selecao();
                break;

            default:
                printf("\nCódigo incorreto, digite novamente.\n");
                break;
        }
    }
}

void ImprimirProduto()
{
    FILE* pr;
    pr = fopen("Industria_sorvete.bin", "rb");

    produto sorvete1;

    if(pr == NULL)
    {
        printf("\nNão foi possível abrir o arquivo");
        exit(1);
    }

    while(fread(&sorvete1, sizeof( struct produto ), 1, pr))
    {
        printf("\nSabor de sorvete: %s", sorvete1.sabor);
        printf("\nPreço do sorvete: R$%.2f\n", sorvete1.valor);
    }
    fclose(pr);
}

void ImprimirFabricacao()
{
    FILE* fb;
    fb = fopen("Fabricacao_sorvete.bin", "rb");

    fabricacao sorvete1;

    if(fb == NULL)
    {
        printf("\nNão foi possível abrir o arquivo");
        exit(1);
    }

    while(fread(&sorvete1, sizeof (struct fabricacao), 1, fb))
    {
        printf("\nData de fabricação: %.2d/%.2d/%.4d", sorvete1.fabricada.dia, sorvete1.fabricada.mes, sorvete1.fabricada.ano);
        printf("\nSabor do sorvete: %s", sorvete1.sorvet.sabor);
        printf("\nValor do sorvete: R$%.2f", sorvete1.sorvet.valor);
        printf("\nQuantidade fabricada: %d\n", sorvete1.fabricado);
    }

    fclose(fb);
}

void ImprimirVenda()
{
    FILE* vd;
    vd = fopen("Venda_sorvete.bin", "rb");

    venda sorvete1;

    if(vd == NULL)
    {
        printf("\nNão foi possível abrir o arquivo");
        exit(1);
    }

    while(fread(&sorvete1, sizeof (struct venda), 1, vd))
    {
        printf("\nData de venda: %.2d/%.2d/%.4d", sorvete1.vendida.dia, sorvete1.vendida.mes, sorvete1.vendida.ano);
        printf("\nSabor do sorvete: %s", sorvete1.sorvet.sabor);
        printf("\nValor do sorvete: R$%.2f", sorvete1.sorvet.valor);
        printf("\nQuantidade vendida: %d\n", sorvete1.vendas);
    }

    fclose(vd);
}

void BuscaFabricacaoData ()
{
    FILE* fb;

    char continuar[] = "s";

    while(strcmp(continuar, "n") != 0)
    {
        fb = fopen("Fabricacao_sorvete.bin", "rb");

        if(fb == NULL)
        {
            puts("\nNão foi possível abrir o arquivo");
            exit(1);
        }

        int dia, mes, ano, j;
        fabricacao sorvete1;

        printf("\nDigite a data a qual deseja pesquisar as fabricações:\n");

        fflush(stdin);
        printf("\nDia: ");
        scanf("%d", &dia);
        fflush(stdin);
        printf("\nMês: ");
        scanf("%d", &mes);
        fflush(stdin);
        printf("\nAno: ");
        scanf("%d", &ano);

        j = 0;

        while(fread(&sorvete1, sizeof(struct fabricacao), 1, fb) == 1)
        {
            if (dia == sorvete1.fabricada.dia && mes == sorvete1.fabricada.mes && ano == sorvete1.fabricada.ano)
            {
                printf("\nData: %.2d/%.2d/%.4d", dia, mes, ano);
                printf("\nSabor: %s", sorvete1.sorvet.sabor);
                printf("\nPreço: R$%.2f", sorvete1.sorvet.valor);
                printf("\nQuantidade fabricada: %d\n", sorvete1.fabricado);
                j = 1;
            }
        }

        fclose(fb);

        if (j == 0)
            printf("\nNenhum sorvete foi fabricado nessa data.\n");

        fflush(stdin);
        printf("\nDeseja pesquisar outra data de fabricação? s/n\n");
        gets(continuar);
    }

}

void BuscaVendaData()
{
    FILE* vd;

    char continuar[] = "s";

    while(strcmp(continuar, "n") != 0)
    {
        vd = fopen("Venda_sorvete.bin", "rb");

        if(vd == NULL)
        {
            puts("\nNão foi possível abrir o arquivo");
            exit(1);
        }

        int dia, mes, ano, j;
        venda sorvete1;

        printf("\nDigite a data a qual deseja pesquisar as vendas:\n");

        fflush(stdin);
        printf("\nDia: ");
        scanf("%d", &dia);
        fflush(stdin);
        printf("\nMês: ");
        scanf("%d", &mes);
        fflush(stdin);
        printf("\nAno: ");
        scanf("%d", &ano);

        j = 0;

        while(fread(&sorvete1, sizeof(struct venda), 1, vd) == 1)
        {
            if (dia == sorvete1.vendida.dia && mes == sorvete1.vendida.mes && ano == sorvete1.vendida.ano)
            {
                printf("\nData: %.2d/%.2d/%.4d", dia, mes, ano);
                printf("\nSabor: %s", sorvete1.sorvet.sabor);
                printf("\nPreço: R$%.2f", sorvete1.sorvet.valor);
                printf("\nQuantidade vendida: %d\n", sorvete1.vendas);
                j = 1;
            }
        }
        fclose(vd);

        if (j == 0)
        {
            printf("\nNenhum sorvete foi vendido nessa data.\n");
            break;
        }

        fflush(stdin);
        printf("\nDeseja pesquisar outra data de venda? s/n\n");
        gets(continuar);
    }
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    Selecao();
}
