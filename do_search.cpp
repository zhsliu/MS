#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <vector>
#include <string>
#include <QMessageBox>
#include <mainwindow.cpp>
#include <mainwindow.h>
#include <QDebug>
#include "define.h"


/***
 * This code read the tree from file and do search.
 */

extern double TF[FILE_SIZE][DICT_SIZE], IDF[DICT_SIZE];
double querytmp[DICT_SIZE];
double querytmp2[2][DICT_SIZE];
double query[2][DICT_SIZE];
double RList[FILE_SIZE][2];
extern double M[2][DICT_SIZE][DICT_SIZE];
extern int SK[];

// 队列结构
extern Node queue[];
extern int front ;
extern int rear ;
extern int itemCount ;
extern Node *insert(Node *data) ;
extern Node *removeData() ;

// 从文件中读取树
Node *file2tree( FILE *fp ) {
    int i, l, r;
    Node tn;
    if( feof(fp) != 0 ) return nullptr;//文件结束返回非0
    // ID
    fscanf(fp, "%d ", &tn.ID);
    // D
    for( i = 0; i < DICT_SIZE; i++ ) {
        fscanf(fp, "%lf ", &tn.D[0][i]);//将fp的内容读出
        fscanf(fp, "%lf ", &tn.D[1][i]);
    }
    // 指针
    fscanf(fp, "%d %d ", &l, &r);
    // FID
    fscanf(fp, "%d ", &tn.FID);
    // 递归调用
    if( l != -1 )//不是叶子节点
        tn.Pl = file2tree( fp );
    else
        tn.Pl = nullptr;
    if( r != -1 )
        tn.Pr = file2tree( fp );
    else
        tn.Pr = nullptr;
    // 检查左右孩子的身份
    if( (tn.Pl != nullptr && l != tn.Pl->ID)
            || (tn.Pr != nullptr && r != tn.Pr->ID ) ) {
        printf("Error at reading Node %3d from file\n", tn.ID);
    }
    return insert(&tn);
}

// search function
void bfsearch(Node *root, double RList[DICT_SIZE][2], int k) {
    int i;
    double result = 0.0;
    // do dot
    for (i = 0; i < DICT_SIZE; i++) {
        result += query[0][i] * root->D[0][i];
        result += query[1][i] * root->D[1][i];
    }
    // 按节点类型划分
    if( root->FID != -1 ) { // leaf node
        if( result > RList[k-1][1] ) {
            // put into RList
            RList[k-1][0] = root->FID;
            RList[k-1][1] = result;
            for( i = k-2; i >= 0; i-- ) {
                if( RList[i][1] < RList[i+1][1] ) {
                    double tmp;
                    tmp           = RList[i  ][0];
                    RList[i  ][0] = RList[i+1][0];
                    RList[i+1][0] = tmp;
                    tmp           = RList[i  ][1];
                    RList[i  ][1] = RList[i+1][1];
                    RList[i+1][1] = tmp;
                }
            }
        }
    } else { // internal node
//        if( result > RList[k-1][1] ) {
            bfsearch(root->Pl, RList, k);
            bfsearch(root->Pr, RList, k);
//        }
    }
    return ;
}

int MainWindow::do_search( std::vector<std::string> Result ) {
    int i, j, k, n, wordindex;
    std::string req;
    double sum;
    FILE *fp;
    Node *root;

    srand( time(nullptr) );
    // 从文件中读取 SK
    fp = fopen(SK_PATH, "r");
    for( i = 0; i < DICT_SIZE; i++ ) {
        fscanf(fp, "%d ", &SK[i]);//从文件中读到数组中
    }
    fclose(fp);

    // 读取矩阵的逆
    fp = fopen(MATRIXinv_PATH, "r");
    for( k = 0; k < 2; k++ ) {
        for( i = 0; i < DICT_SIZE; i++ ) {
            for( j = 0; j < DICT_SIZE; j++ ) {
                fscanf(fp, "%lf ", &M[k][i][j]);
            }
        }
    }
    fclose(fp);

    // 从文件中读取树
    fp = fopen("tree.txt", "r");
    root = file2tree(fp);
    fclose(fp);

    // 从文件中读取 IDF
    fp = fopen("IDF.txt", "r");
    for( i = 0; i < DICT_SIZE; i++ ) {
        fscanf(fp, "%lf ", &IDF[i]);
    }
    fclose(fp);
    //puts("\n\n*** Finish reading from file. ***\n\n");

    // do search
    //初始化tablewidget
    k = std::stoi( Result[0]);//没问题
    n = std::stoi(Result[1]);

    //初始化Tablewidget
    ui->third_result->setColumnCount(3);
    ui->third_result->setHorizontalHeaderLabels(QStringList() << "文件名" << "所在文件夹" << "rank");
    ui->third_result->setRowCount(n);


//    while( 1 ) {
        memset(query, 0, sizeof(querytmp));
        memset(RList, 0, sizeof(RList));

        // 读取搜索请求
//        scanf("%d %d ", &k, &n);//n:关键词个数
//        k = std::stoi( Result[0]);//没问题
//        n = std::stoi(Result[1]);
//        //初始化Tablewidget
//        ui->third_result->setColumnCount(3);
//        ui->third_result->setHorizontalHeaderLabels(QStringList() << "文件名" << "所在文件夹" << "rank");
//        ui->third_result->setRowCount(n);


        for( i = 2; i < Result.size(); i++ ) {
            //scanf("%s", req);
            req = Result[i];//没问题
//            std::cout << req << "\n";
            // check req format
            wordindex = 0;
            for( j = 0; j < req.length(); j++ ) {
                if( !islower(req[j]) ) {
                    wordindex += DICT_SIZE;
                    break;
                }
                wordindex *= 26;
                wordindex += req[j] - 'a';
            }//没问题


            //printf("\tInput %d = '%s'\tindex = %d\n", i, req, wordindex);
//            std::cout << i-2 << req << wordindex <<"\n";
            if( wordindex >= DICT_SIZE ) {
//                puts("Input format Error");
                return 2;
//                break;
            }
            querytmp[ wordindex ] = IDF[ wordindex ];
        }

        // normalize query vector
        sum = 0;
        for( i = 0; i < DICT_SIZE; i++ ) {
            sum += querytmp[i] * querytmp[i];
        }
        sum = sqrt(sum);
        for( i = 0; i < DICT_SIZE; i++ ) {
            querytmp[i] /= sum;
        }

        /* Changed part in BDMRS */
        //
       for( i = 0; i < DICT_SIZE; i++ ) {
            if( SK[i] == 0 ) {
                querytmp2[0][i] = querytmp[i] *rand()/RAND_MAX;
                querytmp2[1][i] = querytmp[i] - querytmp2[0][i];
            } else {
                querytmp2[0][i] = querytmp[i];
                querytmp2[1][i] = querytmp[i];
            }
        }
        for( i = 0; i < DICT_SIZE; i++ ) {
            query[0][i] = 0;
            query[1][i] = 0;
            for( j = 0; j < DICT_SIZE; j++ ) {
                query[0][i] += M[0][i][j] * querytmp2[0][j];
                query[1][i] += M[1][i][j] * querytmp2[1][j];
            }
        }
        /*************************/

        // really do search
        //search(root, RList, k, query);
       bfsearch(root, RList, k);
//        puts("\n\nReaults = ");
        for( i = 0; i < k; i++ ) {
            if( RList[i][1] > 0 ){
//                printf("\tRank%3d = File%4d Score = %lf\n", i+1, (int)RList[i][0], RList[i][1]);
//                std::cout << i+1 << (int)RList[i][0] << RList[i][1] << "\n";
                //设置内容
                ui->third_result->setItem(i,0,new QTableWidgetItem(QString::number((int)RList[i][0])));
                ui->third_result->setItem(i,1,new QTableWidgetItem("/doc"));
                ui->third_result->setItem(i,2,new QTableWidgetItem(QString::number(RList[i][1])));
            }
            else {
                //puts("No more result");
                break;
            }
        }
        //puts("\n\n\n\n");*/
//    }

    return 0;
}
