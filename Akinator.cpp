#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <locale.h>


class TreeNode {
    private:
        std::string question;
        TreeNode* yes;
        TreeNode* no;
        TreeNode* parent;

    public:
        TreeNode () {
            std::string buf = "ABC";
            question = buf;
            yes = NULL;
            no = NULL;
            parent = NULL;
        }

        int LinkTreeNode (TreeNode* parent_, TreeNode* yes_, TreeNode* no_) {
            parent = parent_;
            yes = yes_;
            no = no_;
            return 0;
        }

        ~TreeNode () {
            question.clear();
            yes = NULL;
            no = NULL;
            parent = NULL;
        }

        int ChangeQuestion (std::string question_) {
            question = question_;
            return 0;
        }

        std::string GetQuestion () {
            return question;
        }

        TreeNode* GetYes () {
            return yes;
        }

        TreeNode* GetNo () {
            return no;
        }

        TreeNode* GetParent () {
            return parent;
        }

        int ChangeYes (TreeNode* yes_) {
            yes = yes_;
            return 0;
        }

        int ChangeNo (TreeNode* no_) {
            no = no_;
            return 0 ;
        }

        int ChangeParent (TreeNode* parent_) {
            parent = parent_;
            return 0;
        }
};

class Tree {
    private:
        TreeNode* Root;
        TreeNode* CurNode;

    public:
        Tree () {
            Root = new TreeNode ();
            CurNode = Root;
            Root -> ChangeQuestion("Ваш персонаж реален?");
            AddToYes("Резниченко");
            AddToNo("Луффи де Монки");
            }

        ~Tree () {
            delete Root;
            delete CurNode;
        }

        TreeNode* GetRoot() {
            return Root;
        }

        TreeNode* GetCurNode() {
            return CurNode;
        }

        int GoToYes () {
            CurNode = CurNode -> GetYes();
            return 0;
        }

        int GoToNo () {
            CurNode = CurNode -> GetNo();
            return 0;
        }

        int GoToParent () {
            CurNode = CurNode -> GetParent();
            return 0;
        }

        int GoToRoot () {
            CurNode = Root;
            return 0;
        }

        int AddToYes (std::string object) {
            TreeNode* buf = new TreeNode();
            CurNode -> ChangeYes(buf);
            buf -> ChangeQuestion(object);
            return 0;
        }

        int AddToNo (std::string object) {
            TreeNode* buf = new TreeNode();
            CurNode -> ChangeNo(buf);
            buf -> ChangeQuestion(object);
            return 0;
        }

        int SmartAddToYes (std::string different, std::string object) {
            TreeNode* buf1 = new TreeNode();
            TreeNode* buf2 = new TreeNode();
            CurNode -> ChangeNo(buf1);
            CurNode -> ChangeYes(buf2);
            buf1 -> ChangeParent(CurNode);
            buf2 -> ChangeParent(CurNode);
            buf1 -> ChangeQuestion(CurNode -> GetQuestion());
            buf2 -> ChangeQuestion(object);
            CurNode -> ChangeQuestion(different);

            CurNode = Root;
            return 0;
        }

        int SmartAddToNo (std::string different, std::string object) {
            TreeNode* buf1 = new TreeNode();
            TreeNode* buf2 = new TreeNode();
            CurNode -> ChangeYes(buf1);
            CurNode -> ChangeNo(buf2);
            buf1 -> ChangeParent(CurNode);
            buf2 -> ChangeParent(CurNode);
            buf1 -> ChangeQuestion(CurNode -> GetQuestion());
            buf2 -> ChangeQuestion(object);
            CurNode -> ChangeQuestion(different);

            CurNode = Root;
            return 0;
        }

        int SaveTree () {
            FILE* savefile = NULL;
            savefile = fopen ("savefile.txt", "wb");
            Print(savefile, Root);
            return 0;
        }

        int Print (FILE* savefile, TreeNode* SaveNode) {
        fwrite ("{", sizeof(char), 1, savefile);
        fwrite(SaveNode -> GetQuestion().c_str(), sizeof(char), SaveNode -> GetQuestion().length(), savefile);

            if (SaveNode -> GetYes() != NULL)
                Print(savefile, SaveNode -> GetYes());

            if (SaveNode -> GetNo() != NULL)
                Print(savefile, SaveNode -> GetNo());

            fwrite ("}", sizeof(char), 1, savefile);

            return 0;
        }

        int LoadTree () {
            std::ifstream loadfile("savefile.txt");
            std::string question = "0";
            std::getline(loadfile, question);
            const char* question_c = question.c_str();
            Read(question_c);
            return 0;
        }

        int Read(const char* question) {
            int i = 0;
            int j = 0;
            int k = 0;
            for (;;) {

                if((i == 0) && (question[i] == '{')) {
                    Root = new TreeNode();
                    CurNode = Root;
                    i++;
                    continue;
                }

                if ((question[i] != '{') && (question[i] != '}') && (question[i] != '\0')) {
                    char* buf = new char [strlen(question)];
                    int n = strlen(question);

                    for(k = 0; k <= n - 1; k++)
                        buf[k] = '\0';

                    while((question[i] != '{') && (question[i] != '}')) {
                        buf[j] = question[i];
                        j++; i++;
                    }

                    std::string buf_ = buf;
                    CurNode -> ChangeQuestion(buf_);
                    j = 0;
                    continue;
                }

                if (question[i] == '{') {
                    if (CurNode -> GetYes() == NULL) {
                        TreeNode* Yes = new TreeNode();
                        CurNode -> ChangeYes(Yes);
                        Yes -> ChangeParent(CurNode);
                        CurNode = Yes;
                        i++;
                        continue;
                    }

                    if (CurNode -> GetYes() != NULL) {
                        TreeNode* No = new TreeNode();
                        CurNode -> ChangeNo(No);
                        No -> ChangeParent(CurNode);
                        CurNode = No;
                        i++;
                        continue;
                    }
                }

                if (question[i] == '}') {
                    CurNode = CurNode -> GetParent();
                    i++;
                    continue;
                }

                if (question[i] == '\0') {
                    break;
                }
            }
            return 0;
        }
};


class GuessingManager {
    private:
        char answer;
        Tree* Game;

    public:
        GuessingManager() {
            answer = '0';
            Game = new Tree();
        }

        int MainMenu() {

            for (;;) {
            fflush(stdin);
            printf("Акинатор приветствует Вас!\nНажмите и чтобы играть\nНажмите з чтобы загрузить игру\nНажмите с чтобы сохранить игру\nНажмите в чтобы выйти\n");
            scanf("%c", &answer);

                if(answer == 'и') {
                    PlayGame();
                    continue;
                }

                if (answer == 'з') {
                    Game -> LoadTree();
                    continue;
                }

                if (answer == 'с') {
                    Game -> SaveTree();
                    continue;
                }

                if(answer == 'в')
                    break;

                else {
                    printf("\nНеподходящий ответ!\n\n");
                    continue;
                }
            }

            return 0;
        }

        int PlayGame() {
            Game -> GoToRoot();
            printf("\nНажмите г, чтобы выйти в главное меню\nНажмите д, если Ваш ответ 'да'\nНажмите н, если Ваш ответ 'нет'\n");
            int codenewgame = 0;

            for(;;){
                fflush(stdin);

                if (codenewgame == 0)
                printf ("\n%s\n", Game -> GetCurNode() -> GetQuestion().c_str());

                scanf("%c", &answer);
                if (codenewgame == 0) {

                    if (answer == 'д') {

                        if(Game -> GetCurNode() -> GetYes() == NULL){

                                if (codenewgame == 0) {
                                printf("\nАкинатор выиграл!\n");
                                printf("Начать новую игру?\n");
                                codenewgame = 1;
                                continue;
                                }
                        }

                        Game -> GoToYes();
                        continue;
                    }

                    if (answer == 'н') {

                        if(Game -> GetCurNode() -> GetNo() == NULL){
                                printf("\nАкинатор проиграл(((\n");

                                if (codenewgame == 0) {
                                NewNode();
                                printf("Начать новую игру?\n");
                                codenewgame = 1;
                                continue;
                                }
                            }

                        Game -> GoToNo();
                        continue;
                    }

                    if(answer ==  'г') {
                        printf("\n");
                        break;
                    }

                    else {
                    printf("\nНеподходящий ответ!\n\n");
                    continue;
                    }
                }

                if (codenewgame == 1) {

                     if (answer == 'д') {
                        Game -> GoToRoot();
                        codenewgame = 0;
                        continue;
                     }

                     if (answer == 'н') {
                        printf("\n");
                        break;
                     }
                }
            }
            return 0;
        }

        int NewNode () {
            std::string object = "0";
            std::string different = "0";
            char answer = '0';
            fflush(stdin);
            printf("\nВведите персонажа\n");
            std::getline(std::cin, object);
            printf("\nВведите отличие\n");
            std::getline(std::cin, different);
            different = "Ваш персонаж " + different +"?";

            for (;;) {
                fflush(stdin);
                printf("\nВаш персонаж имеет этот признак?\n");
                scanf("%c", &answer);

                if ((answer == 'д') || (answer == 'н'))
                    break;

                printf("\nНеподходящий ответ!\n\n");
            }

            if (answer == 'д')
                Game -> SmartAddToYes(different, object);

            if (answer == 'н')
                Game -> SmartAddToNo(different, object);

           return 0;
        }
};

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    GuessingManager Akinator;
    Akinator.MainMenu();
    return 0;
}
