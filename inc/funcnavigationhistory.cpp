#include "funcnavigationhistory.h"
#include "command/funcnavigatecommand.h"

#include <QDebug>

void FuncNavigationHistory::executeCommand(const QString &prev, const QString &curr, std::function<void(QString)> func) {
    m_rUndoStack.push(new FuncNavigateCommand(prev, curr, func));
}

void FuncNavigationHistory::undo() {
    if (m_rUndoStack.canUndo()) {
        m_rUndoStack.undo();
    } else {
        qDebug() << "No actions to undo";
    }
}

void FuncNavigationHistory::redo() {
    if (m_rUndoStack.canRedo()) {
        m_rUndoStack.redo();
    } else {
        qDebug() << "No actions to redo";
    }
}

QUndoStack *FuncNavigationHistory::getUndoStack() {
    return &m_rUndoStack;
}
