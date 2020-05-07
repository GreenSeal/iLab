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
            Root -> ChangeQuestion("Âàø ïåðñîíàæ ðåàëåí?");
            AddToYes("Ðåçíè÷åíêî");
            AddToNo("Ëóôôè äå Ìîíêè");
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
            printf("Àêèíàòîð ïðèâåòñòâóåò Âàñ!\nÍàæìèòå è ÷òîáû èãðàòü\nÍàæìèòå ç ÷òîáû çàãðóçèòü èãðó\nÍàæìèòå ñ ÷òîáû ñîõðàíèòü èãðó\nÍàæìèòå â ÷òîáû âûéòè\n");
            scanf("%c", &answer);

                if(answer == 'è') {
                    PlayGame();
                    continue;
                }

                if (answer == 'ç') {
                    Game -> LoadTree();
                    continue;
                }

                if (answer == 'ñ') {
                    Game -> SaveTree();
                    continue;
                }

                if(answer == 'â')
                    break;

                else {
                    printf("\nÍåïîäõîäÿùèé îòâåò!\n\n");
                    continue;
                }
            }

            return 0;
        }

        int PlayGame() {
            Game -> GoToRoot();
            printf("\nÍàæìèòå ã, ÷òîáû âûéòè â ãëàâíîå ìåíþ\nÍàæìèòå ä, åñëè Âàø îòâåò 'äà'\nÍàæìèòå í, åñëè Âàø îòâåò 'íåò'\n");
            int codenewgame = 0;

            for(;;){
                fflush(stdin);

                if (codenewgame == 0)
                printf ("\n%s\n", Game -> GetCurNode() -> GetQuestion().c_str());

                scanf("%c", &answer);
                if (codenewgame == 0) {

                    if (answer == 'ä') {

                        if(Game -> GetCurNode() -> GetYes() == NULL){

                                if (codenewgame == 0) {
                                printf("\nÀêèíàòîð âûèãðàë!\n");
                                printf("Íà÷àòü íîâóþ èãðó?\n");
                                codenewgame = 1;
                                continue;
                                }
                        }

                        Game -> GoToYes();
                        continue;
                    }

                    if (answer == 'í') {

                        if(Game -> GetCurNode() -> GetNo() == NULL){
                                printf("\nÀêèíàòîð ïðîèãðàë(((\n");

                                if (codenewgame == 0) {
                                NewNode();
                                printf("Íà÷àòü íîâóþ èãðó?\n");
                                codenewgame = 1;
                                continue;
                                }
                            }

                        Game -> GoToNo();
                        continue;
                    }

                    if(answer ==  'ã') {
                        printf("\n");
                        break;
                    }

                    else {
                    printf("\nÍåïîäõîäÿùèé îòâåò!\n\n");
                    continue;
                    }
                }

                if (codenewgame == 1) {

                     if (answer == 'ä') {
                        Game -> GoToRoot();
                        codenewgame = 0;
                        continue;
                     }

                     if (answer == 'í') {
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
            printf("\nÂâåäèòå ïåðñîíàæà\n");
            std::getline(std::cin, object);
            printf("\nÂâåäèòå îòëè÷èå\n");
            std::getline(std::cin, different);
            different = "Âàø ïåðñîíàæ " + different +"?";

            for (;;) {
                fflush(stdin);
                printf("\nÂàø ïåðñîíàæ èìååò ýòîò ïðèçíàê?\n");
                scanf("%c", &answer);

                if ((answer == 'ä') || (answer == 'í'))
                    break;

                printf("\nÍåïîäõîäÿùèé îòâåò!\n\n");
            }

            if (answer == 'ä')
                Game -> SmartAddToYes(different, object);

            if (answer == 'í')
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
