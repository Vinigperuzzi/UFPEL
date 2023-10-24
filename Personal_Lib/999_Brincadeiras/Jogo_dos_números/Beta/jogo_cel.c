#include<stdio.h>
#include<stdlib.h>
#include<time.h>


int main()
{
    srand(time(NULL)); //Função srand para gerar um número aleatório, time para usar a data como semente
    int x, y, z, op, var, nj=0, njf=0, njm=0, njd=0, nji=0, njs=0, nvf=0, ndf=0, nvm=0, ndm=0, nvd=0, ndd=0, nvt=0, ndt=0, nvi=0, ndi=0, nvs=0, nds=0;
    char t='n';



    do {
        nj++;
        var=rand() %50;
        if(var==0) {
            var++;
        }

        printf("Escolha um nível de dificuldade\n(1): Fácil\n(2): Médio\n(3): Difícil\n(4): Você está com sorte? (você só terá uma chance)\n");
        scanf("%d",&op);

        while(op<1 || op>5) {
            printf("É pra escolher uma das 4 dificuldades, animal!\n");
            printf("Escolha um nível de dificuldade\n(1): Fácil\n(2): Médio\n(3): Difícil\n(4): Você está com sorte? (você só terá uma chance)\n");
            scanf("%d",&op);
        }



        switch (op) {

        case 1 :
            y=30; njf++;
            while (x!=var && y!=0) {
                y--;
                z=y+1;
                printf("Escolha um número de 1 a 50\n%d chances restante(s)\n",z);
                scanf("%d",&x);
                if(x==var) {
                    printf("\n\nAcertou!");
                    y=30;
                    nvf++;
                }
                if(x>var && x<=50) {
                    printf("O número secreto é menor\n");
                }
                if(x<var && x>0) {
                    printf("O número secreto é maior\n");
                }
                if(x<0 || x>50) {
                    printf("Número inválido\n");
                    y++;
                }
            }
            if(y==0) {
                printf("\n\nPerdeu, fim de jogo.\nO número secreto era: %d",var);
                ndf++;
            }

            break;


        case 2 :
            y=15; njm++;
            while (x!=var && y!=0) {
                y--;
                z=y+1;
                printf("Escolha um número de 1 a 50\n%d chances restante(s)\n",z);
                scanf("%d",&x);
                if(x==var) {
                    printf("\n\nAcertou!");
                    y=15;
                    nvm++;
                }
                if(x>var && x<=50) {
                    printf("O número secreto é menor\n");
                }
                if(x<var && x>0) {
                    printf("O número secreto é maior\n");
                }
                if(x<0 || x>50) {
                    printf("Número inválido\n");
                    y++;
                }
            }
            if(y==0) {
                printf("\n\nPerdeu, fim de jogo.\nO número secreto era: %d",var);
                ndm++;
            }
            break;


        case 3 :
            y=7; njd++;
            while (x!=var && y!=0) {
                y--;
                z=y+1;
                printf("Escolha um número de 1 a 50\n%d chances restante(s)\n",z);
                scanf("%d",&x);
                if(x==var) {
                    printf("\n\nAcertou!");
                    y=7;
                    nvd++;
                }
                if(x>var && x<=50) {
                    printf("O número secreto é menor\n");
                }
                if(x<var && x>0) {
                    printf("O número secreto é maior\n");
                }
                if(x<0 || x>50) {
                    printf("Número inválido\n");
                    y++;
                }
            }
            if(y==0) {
                printf("\n\nPerdeu, fim de jogo.\nO número secreto era: %d",var);
                ndd++;
            }
            break;
            
            case 4 :
            y=1; nji++;
            while (x!=var && y!=0) {
                y--;
                z=y+1;
                printf("Escolha um número de 1 a 50\n%d chances restante(s)\n",z);
                scanf("%d",&x);
                if(x==var) {
                    printf("\n\nAcertou!");
                    y=7;
                    nvi++;
                }
                if(x>var && x<=50) {
                    
                }
                if(x<var && x>0) {
                    
                }
                if(x<0 || x>50) {
                    printf("Número inválido\n");
                    y++;
                }
            }
            if(y==0) {
                printf("\n\nPerdeu, fim de jogo.\nO número secreto era: %d",var);
                ndi++;
            }
            break;
            
            case 5 :
            y=100; njs++; printf("\n\n**Modo secreto habilitado**\n\n");
            printf("O número secreto é: %d\n\n",var);
            while (x!=var && y!=0) {
                y--;
                z=y+1;
                printf("Escolha um número de 1 a 50\n%d chances restante(s)\n",z);
                scanf("%d",&x);
                if(x==var) {
                    printf("\n\nAcertou!");
                    y=7;
                    nvs++;
                }
                if(x>var && x<=50) {
                    printf("O número secreto é menor\n");
                }
                if(x<var && x>0) {
                    printf("O número secreto é maior\n");
                }
                if(x<0 || x>50) {
                    printf("Número inválido\n");
                    y++;
                }
            }
            if(y==0) {
                printf("\n\nComo tu conseguiu errar?, fim de jogo.\nO número secreto era: %d",var);
                nds++;
            }
            break;
            
        default :
            printf("Programa encerrado");
            break;
        }
        printf("\nDeseja jogar de novo: (s/n)\n");
        setbuf(stdin,NULL); // o char é meio complicado
        //se não der o comando setbuf ele pega a última coisa que
        //foi printada e aceita como char
        //então antes de um scanf de char deve-se usar esse
        //comando que limpa o teclado
        scanf("%c",&t);
    } while (t=='s' || t== 'S');
    
    nvt=nvf+nvm+nvd+nvi+nvs; ndt=ndf+ndm+ndd+ndi+nds;
    printf("\n\nRESULTADO:\n\n");

    if(nj==nvt) {
        printf("Perfeito! Você é o melhor!\nVocê fez %d partidas(s) e acertou um número de:\n",nj);
        if (njf>0){
        printf("%d vez(es) no fácil\n",nvf);
    }
        if (njm>0){
        printf("%d vez(es) no médio\n",nvm);
    }
        if (njd>0){
        printf("%d vez(es) no difícil.\n",nvd);
    }
        if (nji>0){
        printf("%d vez(es) no impossível.\n",nvi);
    }
        if (njs>0){
        printf("%d vez(es) no secreto.\n",nvs);
    }
    }
    if(nj>nvt && nvt>ndt) {
        printf("Muito bem! Você jogou muito bem!\nVocê fez %d partida(s) e teve como resultado:\n",nj);
        if (njf>0){
        printf("%d vitória(s) e %d derrota(s) no fácil\n",nvf,ndf);
    }
        if (njm>0){
        printf("%d vitória(s) e %d derrota(s) no médio\n",nvm,ndm);
    }
        if (njd>0){
        printf("%d vitória(s) e %d derrota(s) no difícil.\n",nvd,ndd);
    }
        if (nji>0){
        printf("%d vitória(s) e %d derrota(s) no impossível.\n",nvi,ndi);
    }
        if (njs>0){
        printf("%d vitória(s) e %d derrota(s) no secreto.\n",nvs,nds);
    }
    }
    if(nj!=nvt && nvt<ndt) {
        printf("Que pena!Você fez %d partidas(s) e teve como resultado:\n",nj);
        if (njf>0){
        printf("%d vitória(s) e %d derrota(s) no fácil\n",nvf,ndf);
    }
        if (njm>0){
        printf("%d vitória(s) e %d derrota(s) no médio\n",nvm,ndm);
    }
        if (njd>0){
        printf("%d vitória(s) e %d derrota(s) no difícil.\n",nvd,ndd);
    }
        if (nji>0){
        printf("%d vitória(s) e %d derrota(s) no impossível.\n",nvi,ndi);
    }
        if (njs>0){
        printf("%d vitória(s) e %d derrota(s) no secreto.\n",nvs,nds);
    }
    }
        printf("Fim da reprodução.\n");
        getchar(); // getchar foi meio que uma gambiarra para não ficar dando enter no terminal
    return 0;
}
