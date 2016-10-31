#include <QObject>
#include <QKeySequence>

namespace wb {

class WbOpenListener : public QObject
{
public:
    explicit WbOpenListener(QObject* parent = nullptr);
    void setKeySequenceToOpen(const QKeySequence& sequence);
protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
private:
    bool isOpened;
    QKeySequence keySequenceToOpen;
};

}
