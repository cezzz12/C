//
// Created by Cezar on 24.06.2025.
//

#ifndef SERVICE_H
#define SERVICE_H
#include <QObject>
#include <QList>
#include <algorithm>
#include "domain.h"
#include "repository.h"
#include <QDebug>
class IdeaService : public QObject {
    Q_OBJECT
private:
    QList<Writer> writers;
    QList<Idea> ideas;
public:
    explicit IdeaService(QObject* parent = nullptr) : QObject(parent) {}
    bool loadData(const QString& writersFile, const QString& ideasFile) {
        writers = WriterRepository::loadWriters(writersFile);
        ideas = IdeaRepository::loadIdeas(ideasFile);
        std::sort(ideas.begin(), ideas.end(),
            [](const Idea& a, const Idea& b) {
                return a.getAct() < b.getAct();
            });
        return !writers.isEmpty() && !ideas.isEmpty();
    }
    bool saveData() {
        if (writers.isEmpty() || ideas.isEmpty()) {
            return false;
        }
        return IdeaRepository::saveIdeas("ideas.txt", ideas);
    }
    bool saveDataExplicitly() {
        return saveData();
    }
    const QList<Writer>& getWriters() const { return writers; }
    const QList<Idea>& getIdeas() const { return ideas; }

    //Add a new idea by description and act; idea's crator is the writer that added it; status is proposed
    //Fail if description is empty or act is not 1,2 or 3 or if there is another idea with the same description in same act
    bool addIdea(const QString& description, int act, const QString& writerName, QString& errorMessage) {
        if (description.trimmed().isEmpty()) {
            errorMessage = "Idea description cannot be empty.";
            return false;
        }
        if (act < 1 || act > 3) {
            errorMessage = "Act must be between 1 and 3.";
            return false;
        }
        for (const Idea& idea : ideas) {
            if (idea.getDescription().toLower() == description.toLower() && idea.getAct() == act) {
                errorMessage = "An idea with the same description already exists in this act.";
                return false;
            }
        }
        Writer* writer = nullptr;
        for (const Writer& w : writers) {
            if (w.getName().toLower() == writerName.toLower()) {
                writer = const_cast<Writer*>(&w);
                break;
            }
        }
        if (!writer) {
            errorMessage = "Writer not found.";
            return false;
        }
        ideas.append(Idea(description, "proposed", writer->getName(), act));

        emit ideasChanged();
        return true;
    }
    // Writer can revise idea if it is in proposed status and only writers with senior status can revise ideas
    bool reviseIdea(int index, const QString& newStatus, const QString& writerName, QString& errorMessage) {
        if (index < 0 || index >= ideas.size()) {
            errorMessage = "Invalid idea index.";
            return false;
        }

        // Check if writer exists and is Senior
        Writer* writer = nullptr;
        for (const Writer& w : writers) {
            if (w.getName().toLower() == writerName.toLower()) {
                writer = const_cast<Writer*>(&w);
                break;
            }
        }
        if (!writer) {
            errorMessage = "Writer not found.";
            return false;
        }

        if (writer->getExpertise().toLower() != "senior") {
            errorMessage = "Only Senior writers can revise ideas.";
            return false;
        }

        Idea& idea = ideas[index];
        if (idea.getStatus() != "proposed") {
            errorMessage = "Only proposed ideas can be revised.";
            return false;
        }
        if (newStatus != "accepted" && newStatus != "rejected") {
            errorMessage = "Invalid status. Must be 'accepted' or 'rejected'.";
            return false;
        }
        idea.setStatus(newStatus);
        emit ideasChanged();
        return true;
    }
signals:
    void ideasChanged();
};
#endif //SERVICE_H
