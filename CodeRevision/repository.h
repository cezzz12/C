//
// Created by Cezar on 24.06.2025.
//

#ifndef REPOSITORY_H
#define REPOSITORY_H
#include <QList>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "domain.h"
class ProgrammerRepository {
    public:
        static QList<Programmer> loadProgrammers(const QString &fileName) {
            QList<Programmer> programmers;
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                qDebug() << "Could not open file for reading:" << fileName;
                return programmers;
            }
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                QStringList parts = line.split(",");
                if (parts.size() == 3) {
                    programmers.append(Programmer(parts[0], parts[1].toInt(), parts[2].toInt()));
                }
            }
            file.close();
            return programmers;
        }
};
class SourceFileRepository {
    public:
        static QList<SourceFile> loadSourceFiles(const QString &fileName) {
            QList<SourceFile> sourceFiles;
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                qDebug() << "Could not open file for reading:" << fileName;
                return sourceFiles;
            }
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                QStringList parts = line.split(",");
                if (parts.size() == 4) {
                    sourceFiles.append(SourceFile(parts[0], parts[1], parts[2], parts[3]));
                }
            }
            file.close();
            return sourceFiles;
        }
    static bool saveSourceFiles(const QString &fileName, const QList<SourceFile> &sourceFiles) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Could not open file for writing:" << fileName;
            return false;
        }
        QTextStream out(&file);
        for (const SourceFile &file : sourceFiles) {
            out << file.getName() << "," << file.getStatus() << ","
                << file.getCreator() << "," << file.getReviewer() << "\n";
        }
        file.close();
        return true;
    }
};
#endif //REPOSITORY_H
