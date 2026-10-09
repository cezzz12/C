//
// Created by Cezar on 24.06.2025.
//

#ifndef REPOSITORY_H
#define REPOSITORY_H
#include <QString>
#include <QList>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include "domain.h"
class WriterRepository {
public:
  static QList<Writer> loadWriters(const QString &filename) {
    QList<Writer> writers;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
      qDebug() << "Failed to open file:" << filename;
      return writers;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
      QString line = in.readLine();
      QStringList parts = line.split(",");
      if (parts.size() == 2) {
        writers.append(Writer(parts[0].trimmed(), parts[1].trimmed()));
      }
    }
    file.close();
    return writers;
  }
};
class IdeaRepository {
public:
  static QList<Idea> loadIdeas(const QString &filename) {
    QList<Idea> ideas;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
      qDebug() << "Failed to open file:" << filename;
      return ideas;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
      QString line = in.readLine();
      QStringList parts = line.split(",");
      if (parts.size() == 4) {
        ideas.append(Idea(parts[0].trimmed(), parts[1].trimmed(),
                          parts[2].trimmed(), parts[3].toInt()));
      }
    }
    file.close();
    return ideas;
  }
  static bool saveIdeas(const QString &filename, const QList<Idea> &ideas) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
      qDebug() << "Failed to open file for writing:" << filename;
      return false;
    }
    QTextStream out(&file);
    for (const Idea &idea : ideas) {
      out << idea.getDescription() << ","
          << idea.getStatus() << ","
          << idea.getCreator() << ","
          << idea.getAct() << "\n";
    }
    file.close();
    return true;
  }
};
#endif //REPOSITORY_H
