//
// Created by Cezar on 24.06.2025.
//

#ifndef DOMAIN_H
#define DOMAIN_H
#include <QString>

class Programmer {
private:
    QString name;
    int revised_files;
    int remaining_files;
public:
    Programmer() : revised_files(0), remaining_files(0) {}
    Programmer(const QString &name, int revised_files, int remaining_files)
        : name(name), revised_files(revised_files), remaining_files(remaining_files) {}

    QString getName() const { return name; }
    int getRevisedFiles() const { return revised_files; }
    int getRemainingFiles() const { return remaining_files; }

    void setName(const QString &newName) { name = newName; }
    void setRevisedFiles(int newRevisedFiles) { revised_files = newRevisedFiles; }
    void setRemainingFiles(int newRemainingFiles) { remaining_files = newRemainingFiles; }
};
class SourceFile{
  private:
    QString name;
    QString status;
    QString creator;
    QString reviewer;
  public:
    SourceFile(const QString &name, const QString &status, const QString &creator, const QString &reviewer)
        : name(name), status(status), creator(creator), reviewer(reviewer) {}

    QString getName() const { return name; }
    QString getStatus() const { return status; }
    QString getCreator() const { return creator; }
    QString getReviewer() const { return reviewer; }

    void setName(const QString &newName) { name = newName; }
    void setStatus(const QString &newStatus) { status = newStatus; }
    void setCreator(const QString &newCreator) { creator = newCreator; }
    void setReviewer(const QString &newReviewer) { reviewer = newReviewer; }

};
#endif //DOMAIN_H
