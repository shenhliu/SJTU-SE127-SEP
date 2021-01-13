/*
基本实现了PDF要求的功能，但是有些地方还是不太完善
1.因为偷懒直接用了Console显示了提示和变量表，也就是说用户可以对这两个区域进行修改(尽管不会对程序影响产生影响)
2.因为Console是使用回车键作为一条statement的结束，并进行存储的。这就造成了一旦按下回车键，就不能再直接在console里进行修改的情况，
 必须再写一行进行覆盖。。如果强行修改的话也不会进行存储，会报错或者导致运行错误。
3.程序的架构问题很大，理论上讲RUN之类的函数都应该在statement里实现，但是图方便都放到了mainwindow里，导致mainwindow里代码量爆炸，也不好修改
4.后期修改的时候，为了图方便，都是加代码，而不是对原来的代码进行修改。如重写了个ConditionRun,其实都是复制了RUN，完全可以写成一个函数。
*/

//第二版加入了处理死循环的机制


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"console.h"
#include <QLabel>
#include <QApplication>
#include<QMap>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("BASIC");
    this->setFixedSize(900, 900);

    Parser = new parser;   //初始化parser

    Tokenizer = new tokenizer;          //初始化分割器

    console = new Console(this);       //初始化代码输入区
    console->setGeometry(0, 0, 600, 600);

    markconsole = new Console(this);
    markconsole->setGeometry(0,600,20,300);

    inputconsole = new Console(this);    //初始化变量赋值区
    inputconsole->setGeometry(20,600,600,300);

    Tipconsole = new Console(this);         //初始化报错和帮助区
    Tipconsole->setGeometry(600,450,300,450);

    varmap = new Console(this);            //初始化显示变量的区域
    varmap->setGeometry(600,0,300,450);

    pro = new program();               //初始化链表
    connect(console,SIGNAL(newLineWritten(QString)),this,SLOT(newStatement(QString)));
    connect(inputconsole,SIGNAL(newLineWritten(QString)),this,SLOT(newInput(QString)));

    breakpoints = new program;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newStatement(QString statement)   //这里把QString命名为statement其实是一个失误，与类statement重名了。
//这使得在这个函数里，无法再声明statement类型的变量。。 时间如果够的话会再回头改
{
    QList<QString> tmplist = statement.split(' ',QString::SkipEmptyParts);
    bool ok;
    if(statement == nullptr) {return;}
    if(statement ==" ") {return;}
    if(statement == "HELP")
    {
        Tipconsole->write("普通的使用方法可以参照PDF，已经实现了PDF要求的功能");
        Tipconsole->write("左上角输入你要写的代码");
        Tipconsole->write("左下角用来输入INPUT的值");
        Tipconsole->write("右上角显示目前定义的变量，DEBUG和RUN时都会更新");
        Tipconsole->write("右下角显示各类提示");
        Tipconsole->write("必须手动输入，复制粘贴的代码不认！会出错");
        Tipconsole->write("完成一行代码后，按回车写下一行代码，不能再对之前的代码进行修改");
        Tipconsole->write("如果要修改之前写的代码，可以再写一行进行覆盖");
        Tipconsole->write("不要试图修改右上角和右下角区域的代码");
        Tipconsole->write("可以输入DEBUG来进行调试，输入后右下角会有相关提示");
        return;
    }
    if(statement == "CLEAR")
    {
        pro->clear();
        delete pro;
        pro = new program();
        console->setPlainText("");
        Tipconsole->setPlainText("");
        markconsole->setPlainText("");
        return;
    }
    if(statement == "QUIT")
    {
        this->close();
    }
    if(statement =="LIST")
    {
        traverse();
        return;
    }
    if(statement == "RUN")
    {
        circletimes = 0;
        Tipconsole->setText("");
        RunThePro(Vars,pro->head->next);
        return;
    }
    if(tmplist[0] == "INPUT")
    {
        markconsole->write("?");
        inputvar = tmplist[1];
        RunThePro(Vars,pro->head->next);
        return;
    }
    if(tmplist[0] == "PRINT")
    {
        RunThePro(Vars,pro->head->next);
        QString sta = "";
        for(int i = 1;i < tmplist.length();++i)   //这个循环是为了去掉"PRINT" 获得一个纯正的expression
        {
            sta += tmplist[i];
        }

        QList<QString>tokens;
        tokens.clear();
        tokens = Tokenizer->ToTokens(sta);

        Expression*val;

        try {
            val = Parser->ToTree(tokens);                   //化成表达树
        } catch (QString errorTips) {
            QString Tips = "";
            Tips += " ";
            Tips += errorTips;
            Tipconsole->write(Tips);
            return;
        }

        int num;

        try {
            num = val->eval(Vars);                               //进行求值
        } catch (QString errorTips) {
            QString Tips = "";
            Tips += " ";
            Tips += errorTips;
            Tipconsole->write(Tips);
            return;
        }

        QString tmp = QString::number(num,10);
        console->write(tmp);
    }

    if(statement == "DEBUG")
    {
        Tipconsole->setText("");
        QString Tip = "";
        Tip += "You can debug now.\nInput \"B linenum\" to set a breakpoint.\n";
        Tip += "Input \"DELETE linenum\" to delete the breakpoint.\n";
        Tip += "Input \"STEP\" for Single step debugging\n";
        Tip += "Input \"CONTINUE\"to reach the next breakpoint\n";
        Tip += "Input \"LISTB\" to see all the breakpoints";

        Tipconsole->write(Tip);
        curbpoint = pro->head->next;

        if(curbpoint != nullptr)
        {
            breakpoints->insert(curbpoint->getlinenum(),(curbpoint->gettext()));
            curbpoint = breakpoints->head->next;
            ifdebug = true;
        }
    }

    if(tmplist[0] == "B")
    {
        bool ok;
        tmplist[1].toInt(&ok);
        if(!ok)
        {
            Tipconsole->write("There must be a number after \"B\".");
            return;
        }
        int lnum = tmplist[1].toInt();

        findpointer = pro->head->next;

        while (findpointer!=nullptr)
        {
            QList<QString> tmpst = findpointer->text.split(' ',QString::SkipEmptyParts);
            if(tmpst[0].toInt() == lnum)
            {
                break;
            }
            findpointer = findpointer->next;
        }
        if(findpointer == nullptr)    //没有找到目标行号
        {
            QString t = "";
            t += "The linenumber is invalid.";
            Tipconsole->write(t);
            return;
        }
        else {                //找到了目标行号,就插到breakpoints里面去
            breakpoints->insert(lnum,findpointer->gettext());
        }
    }

    if(tmplist[0] == "DELETE")
    {
        bool ok;
        tmplist[1].toInt(&ok);
        if(!ok)
        {
            QString t = "";
            t += "The linenumber is invalid.";
            Tipconsole->write(t);
            return;
        }

        int delnum = tmplist[1].toInt();
        breakpoints->del(delnum);             //如果删一个不存在的statement，什么都不做。
    }

    if(statement == "CONTINUE")
    {
        findpointer = pro->findline(curbpoint->getlinenum());
        if(!ifdebug)
        {
            Tipconsole->write("Please input\"DEBUG\"first");
            return;
        }
        if(curbpoint->next == nullptr)
        {
            ConditionRun(Vars,findpointer,nullptr);
            ifdebug = false;
            return;
        }
        findpointer2 = pro->findline(curbpoint->next->getlinenum());

        ConditionRun(Vars,findpointer,findpointer2);
        curbpoint = curbpoint->next;

        QString Tips = "";
        Tips += "You are at ";
        Tips += QString::number(curbpoint->linenum);
        Tips += ".";
        Tipconsole->write(Tips);
        //varmap->setText(Vars.Tranvrese());
    }

    if(statement == "LISTB")
    {
        tranverseBp();
    }

    if(statement == "STEP")
    {
        findpointer = pro->findline(curbpoint->getlinenum());
        if(!ifdebug)
        {
            Tipconsole->write("Please input\"DEBUG\"first");
            return;
        }
        if(curbpoint->next == nullptr)
        {
            ConditionRun(Vars,findpointer,nullptr);
            ifdebug = false;
            return;
        }
        ConditionRun(Vars,findpointer,findpointer->next);
        curbpoint = findpointer->next;

        QString Tips = "";
        Tips += "You are at ";
        Tips += QString::number(curbpoint->linenum);
        Tips += ".";
        Tipconsole->write(Tips);
        //varmap->setText(Vars.Tranvrese());
    }


    if(tmplist[0]!=nullptr)
    {
        tmplist[0].toInt(&ok);
        if(ok)
        {
            int tmplinenum = tmplist[0].toInt();
            pro->insert(tmplinenum,statement);
        }
    }
    if(statement!= nullptr && statement != " " && statement != "HELP" && statement != "CLEAR"
            && statement != "QUIT" && statement != "LIST" && statement != "RUN"
            && tmplist[0] != "PRINT" && !IsConstantexp(tmplist[0]) && statement!="DEBUG"
            && tmplist[0]!= "DELETE" && statement !="CONTINUE" && tmplist[0] != "B" &&
            statement != "LISTB" && statement != "STEP" &&statement != "INPUT")
    {
        Tipconsole->write("Wrong command!");
        return;
    }

}

void MainWindow::traverse()          //用来遍历所有的statement，即完成“LIST”操作
{
    statement *p = pro->head->next;
    while(p!=nullptr)
    {
        console->write(p->text);
        p = p->next;
    }
}

void MainWindow::tranverseBp()
{
    statement *p = breakpoints->head->next;
    while(p!=nullptr)
    {
        console->write(p->text);
        p = p->next;
    }
}


void MainWindow::RunThePro(evalstate &Vars,statement*runpos)
{
    statement * cur = runpos;
    while(cur!=nullptr)
    {
        circletimes++;
        if(circletimes == 10000)
        {
            Tipconsole->write("You cause a dead cycle.");
            return;
        }

        QList<QString> tmpstatements = cur->text.split(' ',QString::SkipEmptyParts);
        if(tmpstatements[1] == "END")
        {
            break;
        }

        else if(tmpstatements[1] == "REM")
        {
            cur = cur->next;
            continue;
        }

        else if(tmpstatements[1] == "LET")
        {
            QString sta = "";
            for(int i = 2;i < tmpstatements.length();++i)   //这个循环是为了去掉"LET" 获得一个纯正的expression
            {
                sta += tmpstatements[i];
            }

            QList<QString>tokens;
            tokens.clear();
            tokens = Tokenizer->ToTokens(sta);

            Expression*val;

            try {
                val = Parser->ToTree(tokens);                   //化成表达树
            } catch (QString errorTips) {
                QString Tips = "";
                Tips += " ";
                Tips += errorTips;
                Tipconsole->write(Tips);
            }
            try {
                val->eval(Vars);                               //进行求值
            } catch (QString errorTips) {
                QString Tips = "";
                Tips += QString::number(cur->linenum);
                Tips += " ";
                Tips += errorTips;
                Tipconsole->write(Tips);
                return;
            }

//            QString ceshi = QString(num);         //测试留下来的东西，不必在意
//            Tipconsole->write(ceshi);
        }

        else if(tmpstatements[1] == "PRINT")
        {
            QString sta = "";
            for(int i = 2;i < tmpstatements.length();++i)   //这个循环是为了去掉"PRINT" 获得一个纯正的expression
            {
                sta += tmpstatements[i];
            }
            QList<QString>tokens;
            tokens.clear();
            tokens = Tokenizer->ToTokens(sta);
            //Expression*val = Parser->ToTree(tokens);                   //化成表达树

            Expression*val;

            try {
                val = Parser->ToTree(tokens);                   //化成表达树
            } catch (QString errorTips) {
                QString Tips = "";
                Tips += " ";
                Tips += errorTips;
                Tipconsole->write(Tips);
                return;
            }

            int num;

            try {
                num = val->eval(Vars);                               //进行求值
            } catch (QString errorTips) {
                QString Tips = "";
                Tips += QString::number(cur->linenum);
                Tips += " ";
                Tips += errorTips;
                Tipconsole->write(Tips);
                return;
            }

            QString tmp = QString::number(num,10);
            console->write(tmp);
        }

        else if(tmpstatements[1] =="INPUT")
        {
            markconsole->write("?");
            inputvar = tmpstatements[2];
            inputpos = cur;
            return;
        }

        else if(tmpstatements[1] == "IF")
        {
            QString sta = "";
            for(int i = 2;i < tmpstatements.length();++i)   //找到IF和THEN之间的判断条件
            {
                if(tmpstatements[i] == "THEN")
                    break;
                else
                    sta += tmpstatements[i];
            }
            bool ok ;

            try {
                ok = IfCondition(sta);
            } catch (QString errorTips) {
                QString err = "";
                err += QString::number(cur->linenum);
                err += " ";
                err += errorTips;
                Tipconsole->write(err);
                return;
            }

            if(ok)           //如果if条件成立，就去找then
            {
                int j = 0;
                for(j = 0;j<tmpstatements.length();++j)
                {
                    if(tmpstatements[j] == "THEN")
                        break;
                }
                if(j == tmpstatements.length()-1)
                {
                    QString t = "";
                    t += QString::number(cur->linenum);
                    t += " ";
                    t += "No linenumber is input!";
                    Tipconsole->write(t);
                    return;
                }
                int desnum = tmpstatements[j+1].toInt();
                statement*tmp = pro->head->next;
                while (tmp!=nullptr)
                {
                    QList<QString> tmpst = tmp->text.split(' ',QString::SkipEmptyParts);
                    if(tmpst[0].toInt() == desnum)
                    {
                        break;
                    }
                    tmp = tmp->next;
                }
                if(tmp == nullptr)
                {
                    QString t = "";
                    t += QString::number(cur->linenum);
                    t += " ";
                    t += "The linenumber is invalid！";
                    Tipconsole->write(t);
                    return;
                }
                cur = tmp;
                continue;
            }
        }

        else if(tmpstatements[1] == "GOTO")
        {
            bool ok;
            tmpstatements[2].toInt(&ok);
            if(ok)
            {
                int desnum = tmpstatements[2].toInt();       //要跳转的行号
                statement*tmp = pro->head->next;
                while (tmp!=nullptr)
                {                  
                    QList<QString> tmpst = tmp->text.split(' ',QString::SkipEmptyParts);
                    if(tmpst[0].toInt() == desnum)
                    {
                        break;
                    }
                    tmp = tmp->next;
                }
                if(tmp == nullptr)
                {
                    QString t = "";
                    t += QString::number(cur->linenum);
                    t += " ";
                    t += "The linenumber is invalid！";
                    Tipconsole->write(t);
                    return;
                    //报错，没有找到这一行
                }
                cur = tmp;
                continue;
            }
            else {
                QString t = "";
                t += QString::number(cur->linenum);
                t += " ";
                t += "No linenumber is input";
                Tipconsole->write(t);
                return;
                //写报错条件,没有写正确的行号
            }
        }

        else {
            QString t = "";
            t += QString::number(cur->linenum);
            t += " ";
            t += "The statemenr is invalid!";
            Tipconsole->write(t);
            return;
        }

        cur = cur->next;
    }
    varmap->setText(Vars.Tranvrese());
}

void MainWindow::newInput(QString inp)
{
    inp.remove(" ");
    int num = inp.toInt();
    Vars.setValue(inputvar,num);
    if(inputpos->next!=nullptr)
        RunThePro(Vars,inputpos->next);
}

bool MainWindow::IfCondition(QString str)
{
    if(str.contains("="))
    {
        QList<QString> ifstrs = str.split('=',QString::SkipEmptyParts);

        QList<QString>tokensleft;
        tokensleft.clear();
        tokensleft = Tokenizer->ToTokens(ifstrs[0]);
        //Expression*valleft = Parser->ToTree(tokensleft);                   //化成表达树
        Expression*valleft;

        try {
            valleft = Parser->ToTree(tokensleft);                   //化成表达树
        } catch (QString errorTips) {
            QString Tips = "";
            Tips += " ";
            Tips += errorTips;
            Tipconsole->write(Tips);
        }
        int numleft ;
        QString err;
        try {
            numleft = valleft->eval(Vars);                                        //进行求值
        } catch (QString errorTips) {
            err = errorTips;
            throw err;
        }

        QList<QString>tokensright;
        tokensright.clear();
        tokensright = Tokenizer->ToTokens(ifstrs[1]);
        //Expression*valright = Parser->ToTree(tokensright);                   //化成表达树
        Expression*valright;

        try {
            valright = Parser->ToTree(tokensright);                   //化成表达树
        } catch (QString errorTips) {
            QString Tips = "";
            Tips += " ";
            Tips += errorTips;
            Tipconsole->write(Tips);
        }
        int numright ;                             //进行求值
        QString err2;
        try {
            numright = valright->eval(Vars);                                        //进行求值
        } catch (QString errorTips) {
            err = errorTips;
            throw err;
        }

        if(numleft == numright)
        {
            return true;
        }
        else {
            return false;
        }
    }
    else if (str.contains(">")) {
        QList<QString> ifstrs = str.split('>',QString::SkipEmptyParts);
        QList<QString>tokensleft;
        tokensleft.clear();
        tokensleft = Tokenizer->ToTokens(ifstrs[0]);
        //Expression*valleft = Parser->ToTree(tokensleft);                   //化成表达树
        Expression*valleft;

        try {
            valleft = Parser->ToTree(tokensleft);                   //化成表达树
        } catch (QString errorTips) {
            QString Tips = "";
            Tips += " ";
            Tips += errorTips;
            Tipconsole->write(Tips);
        }
        int numleft ;
        QString err;
        try {
            numleft = valleft->eval(Vars);                                        //进行求值
        } catch (QString errorTips) {
            err = errorTips;
            throw err;
        }

        QList<QString>tokensright;
        tokensright.clear();
        tokensright = Tokenizer->ToTokens(ifstrs[1]);
        //Expression*valright = Parser->ToTree(tokensright);                   //化成表达树
        Expression*valright;

        try {
            valright = Parser->ToTree(tokensright);                   //化成表达树
        } catch (QString errorTips) {
            QString Tips = "";
            Tips += " ";
            Tips += errorTips;
            Tipconsole->write(Tips);
        }
        int numright ;                             //进行求值
        QString err2;
        try {
            numright = valright->eval(Vars);                                        //进行求值
        } catch (QString errorTips) {
            err = errorTips;
            throw err;
        }

        if(numleft > numright)
        {
            return true;
        }
        else {
            return false;
        }
    }
    else if (str.contains("<")) {
        QList<QString> ifstrs = str.split('<',QString::SkipEmptyParts);
        QList<QString>tokensleft;
        tokensleft.clear();
        tokensleft = Tokenizer->ToTokens(ifstrs[0]);
        //Expression*valleft = Parser->ToTree(tokensleft);                   //化成表达树
        Expression*valleft;

        try {
            valleft = Parser->ToTree(tokensleft);                   //化成表达树
        } catch (QString errorTips) {
            QString Tips = "";
            Tips += " ";
            Tips += errorTips;
            Tipconsole->write(Tips);
        }
        int numleft ;
        QString err;
        try {
            numleft = valleft->eval(Vars);                                        //进行求值
        } catch (QString errorTips) {
            err = errorTips;
            throw err;
        }

        QList<QString>tokensright;
        tokensright.clear();
        tokensright = Tokenizer->ToTokens(ifstrs[1]);
        //Expression*valright = Parser->ToTree(tokensright);                   //化成表达树
        Expression*valright;

        try {
            valright = Parser->ToTree(tokensright);                   //化成表达树
        } catch (QString errorTips) {
            QString Tips = "";
            Tips += " ";
            Tips += errorTips;
            Tipconsole->write(Tips);
        }
        int numright ;                             //进行求值
        QString err2;
        try {
            numright = valright->eval(Vars);                                        //进行求值
        } catch (QString errorTips) {
            err = errorTips;
            throw err;
        }

        inputconsole->write(QString::number(numleft));

        if(numleft < numright)
        {
            return true;
        }
        else {
            return false;
        }


    }
    else {
        QList<QString> ifstrs;
    }
    return false;
}

bool MainWindow::IsConstantexp(QString exp)
{
    bool ok;
    exp.toInt(&ok);
    return ok;
}

void MainWindow::ConditionRun(evalstate &Vars, statement *current, statement *breakpoint)
{//这个函数大段复制了RUN。。。其实写的很臭，但是因为是后期修改的，也没想把前面的RUN重写一遍然后在这重用了，其实是偷了个懒，使得代码看起来很冗余

   statement*cur = current;
    while(cur!=nullptr)
    {

        QList<QString> tmpstatements = cur->text.split(' ',QString::SkipEmptyParts);
        if(tmpstatements[1] == "END")
        {
            break;
        }

        else if(tmpstatements[1] == "REM")
        {
            cur = cur->next;
            continue;
        }

        else if(tmpstatements[1] == "LET")
        {
            QString sta = "";
            for(int i = 2;i < tmpstatements.length();++i)   //这个循环是为了去掉"LET" 获得一个纯正的expression
            {
                sta += tmpstatements[i];
            }

            QList<QString>tokens;
            tokens.clear();
            tokens = Tokenizer->ToTokens(sta);

            Expression*val;

            try {
                val = Parser->ToTree(tokens);                   //化成表达树
            } catch (QString errorTips) {
                QString Tips = "";
                Tips += " ";
                Tips += errorTips;
                Tipconsole->write(Tips);
            }
            try {
                val->eval(Vars);                               //进行求值
            } catch (QString errorTips) {
                QString Tips = "";
                Tips += QString::number(cur->linenum);
                Tips += " ";
                Tips += errorTips;
                Tipconsole->write(Tips);
                return;
            }

//            QString ceshi = QString(num);         //测试留下来的东西，不必在意
//            Tipconsole->write(ceshi);
        }

        else if(tmpstatements[1] == "PRINT")
        {
            QString sta = "";
            for(int i = 2;i < tmpstatements.length();++i)   //这个循环是为了去掉"PRINT" 获得一个纯正的expression
            {
                sta += tmpstatements[i];
            }
            QList<QString>tokens;
            tokens.clear();
            tokens = Tokenizer->ToTokens(sta);
            //Expression*val = Parser->ToTree(tokens);                   //化成表达树

            Expression*val;

            try {
                val = Parser->ToTree(tokens);                   //化成表达树
            } catch (QString errorTips) {
                QString Tips = "";
                Tips += " ";
                Tips += errorTips;
                Tipconsole->write(Tips);
            }

            int num;

            try {
                num = val->eval(Vars);                               //进行求值
            } catch (QString errorTips) {
                QString Tips = "";
                Tips += QString::number(cur->linenum);
                Tips += " ";
                Tips += errorTips;
                Tipconsole->write(Tips);
                return;
            }

            QString tmp = QString::number(num,10);
            console->write(tmp);
        }

        else if(tmpstatements[1] =="INPUT")
        {
            markconsole->write("?");
            inputvar = tmpstatements[2];
            inputpos = cur;
            return;
        }

        else if(tmpstatements[1] == "IF")
        {
            QString sta = "";
            for(int i = 2;i < tmpstatements.length();++i)   //找到IF和THEN之间的判断条件
            {
                if(tmpstatements[i] == "THEN")
                    break;
                else
                    sta += tmpstatements[i];
            }
            bool ok ;

            try {
                ok = IfCondition(sta);
            } catch (QString errorTips) {
                QString err = "";
                err += QString::number(cur->linenum);
                err += " ";
                err += errorTips;
                Tipconsole->write(err);
                return;
            }

            if(ok)           //如果if条件成立，就去找then
            {
                int j = 0;
                for(j = 0;j<tmpstatements.length();++j)
                {
                    if(tmpstatements[j] == "THEN")
                        break;
                }
                if(j == tmpstatements.length()-1)
                {
                    QString t = "";
                    t += QString::number(cur->linenum);
                    t += " ";
                    t += "No linenumber is input!";
                    Tipconsole->write(t);
                    return;
                }
                int desnum = tmpstatements[j+1].toInt();
                statement*tmp = pro->head->next;
                while (tmp!=nullptr)
                {
                    QList<QString> tmpst = tmp->text.split(' ',QString::SkipEmptyParts);
                    if(tmpst[0].toInt() == desnum)
                    {
                        break;
                    }
                    tmp = tmp->next;
                }
                if(tmp == nullptr)
                {
                    QString t = "";
                    t += QString::number(cur->linenum);
                    t += " ";
                    t += "The linenumber is invalid！";
                    Tipconsole->write(t);
                    return;
                }
                cur = tmp;
                continue;
            }
        }

        else if(tmpstatements[1] == "GOTO")
        {
            bool ok;
            tmpstatements[2].toInt(&ok);
            if(ok)
            {
                int desnum = tmpstatements[2].toInt();       //要跳转的行号
                statement*tmp = pro->head->next;
                while (tmp!=nullptr)
                {
                    QList<QString> tmpst = tmp->text.split(' ',QString::SkipEmptyParts);
                    if(tmpst[0].toInt() == desnum)
                    {
                        break;
                    }
                    tmp = tmp->next;
                }
                if(tmp == nullptr)
                {
                    QString t = "";
                    t += QString::number(cur->linenum);
                    t += " ";
                    t += "The linenumber is invalid！";
                    Tipconsole->write(t);
                    return;
                    //报错，没有找到这一行
                }
                cur = tmp;
                continue;
            }
            else {
                QString t = "";
                t += QString::number(cur->linenum);
                t += " ";
                t += "No linenumber is input";
                Tipconsole->write(t);
                return;
                //写报错条件,没有写正确的行号
            }
        }

        else {
            QString t = "";
            t += QString::number(cur->linenum);
            t += " ";
            t += "The statemenr is invalid!";
            Tipconsole->write(t);
            return;
        }
        varmap->setText(Vars.Tranvrese());
        cur = cur->next;
        if(cur == breakpoint)
            return;
    }

}




















