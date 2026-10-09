#ifndef SERVICE_H
#define SERVICE_H
#include "domain.h"
#include "repository.h"
#include <QObject>
#include <QList>
#include <algorithm>

class FileService : public QObject {
    Q_OBJECT
private:
    QList<Programmer> programmers;
    QList<SourceFile> sourceFiles;

public:
    explicit FileService(QObject* parent = nullptr) : QObject(parent) {}

    bool loadData(const QString& programmersFile, const QString& sourceFilesFile) {
        programmers = ProgrammerRepository::loadProgrammers(programmersFile);
        sourceFiles = SourceFileRepository::loadSourceFiles(sourceFilesFile);
        std::sort(sourceFiles.begin(), sourceFiles.end(),
            [](const SourceFile& a, const SourceFile& b) {
                return a.getName() < b.getName();
            });
        return !programmers.isEmpty() && !sourceFiles.isEmpty();
    }
    bool saveData() {
        if (programmers.isEmpty() || sourceFiles.isEmpty()) {
            return false;
        }
        return SourceFileRepository::saveSourceFiles("source_files.txt", sourceFiles);
    }

    const QList<Programmer>& getProgrammers() const { return programmers; }
    const QList<SourceFile>& getSourceFiles() const { return sourceFiles; }
    
    Programmer* findProgrammer(const QString& name) {
        for (int i = 0; i < programmers.size(); ++i) {
            if (programmers[i].getName() == name) {
                return &programmers[i];
            }
        }
        return nullptr;
    }

    bool addFile(const QString& name, const QString& creator, QString& errorMessage) {
        if (name.trimmed().isEmpty()) {
            errorMessage = "File name cannot be empty.";
            return false;
        }
        
        // Check if file already exists
        for (const SourceFile& file : sourceFiles) {
            if (file.getName().toLower() == name.trimmed().toLower()) {
                errorMessage = "A file with this name already exists.";
                return false;
            }
        }
        
        sourceFiles.append(SourceFile(name.trimmed(), "not revised", creator, ""));
        std::sort(sourceFiles.begin(), sourceFiles.end(),
            [](const SourceFile& a, const SourceFile& b) {
                return a.getName() < b.getName();
            });
        
        emit filesChanged();
        return true;
    }

    bool reviseFile(const QString& fileName, const QString& reviewer, QString& errorMessage) {
        for (int i = 0; i < sourceFiles.size(); ++i) {
            if (sourceFiles[i].getName() == fileName) {
                if (sourceFiles[i].getStatus() == "revised") {
                    errorMessage = "File is already revised.";
                    return false;
                }
                if (sourceFiles[i].getCreator() == reviewer) {
                    errorMessage = "You cannot revise your own files.";
                    return false;
                }
                
                sourceFiles[i].setStatus("revised");
                sourceFiles[i].setReviewer(reviewer);
                
                // Update programmer statistics
                Programmer* programmer = findProgrammer(reviewer);
                if (programmer) {
                    programmer->setRevisedFiles(programmer->getRevisedFiles() + 1);
                    programmer->setRemainingFiles(programmer->getRemainingFiles() - 1);
                }
                
                emit filesChanged();
                return true;
            }
        }
        errorMessage = "File not found.";
        return false;
    }

    int getRevisedFilesCount(const QString& programmerName) const {
        int count = 0;
        for (const SourceFile& file : sourceFiles) {
            if (file.getReviewer() == programmerName && file.getStatus() == "revised") {
                count++;
            }
        }
        return count;
    }

    int getRemainingFilesCount(const QString& programmerName) const {
        const Programmer* programmer = nullptr;
        for (const Programmer& p : programmers) {
            if (p.getName() == programmerName) {
                programmer = &p;
                break;
            }
        }
        return programmer ? programmer->getRemainingFiles() : 0;
    }
    bool saveDataExplicitly() {
        return saveData();
    }

signals:
    void filesChanged();
};
#endif