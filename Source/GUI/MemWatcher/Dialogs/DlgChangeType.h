#pragma once

#include <QComboBox>
#include <QDialog>
#include <QSpinBox>

#include "../../../Common/CommonTypes.h"

class DlgChangeType : public QDialog
{
  Q_OBJECT

public:
  DlgChangeType(QWidget* parent, const int typeIndex, const size_t length, u8 flagValue);
  int getTypeIndex() const;
  size_t getLength() const;
  u8 getFlagValue() const;
  void accept();
  void onTypeChange(int index);

private:
  void initialiseWidgets();
  void makeLayouts();

  int m_typeIndex;
  size_t m_length;
  u8 m_flagValue;
  QComboBox* m_cmbTypes;
  QSpinBox* m_spnLength;
  QSpinBox* m_spnFlag;
  QWidget* m_lengthSelection;
  QWidget* m_flagSelection;
};
