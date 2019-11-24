#include "DlgChangeType.h"

#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>

#include "../../GUICommon.h"

DlgChangeType::DlgChangeType(QWidget* parent, const int typeIndex, const size_t length,
                             u8 flagValue)
    : QDialog(parent), m_typeIndex(typeIndex), m_length(length), m_flagValue(flagValue)
{
  initialiseWidgets();
  makeLayouts();
}

void DlgChangeType::initialiseWidgets()
{
  m_cmbTypes = new QComboBox(this);
  m_cmbTypes->addItems(GUICommon::g_memTypeNames);
  m_cmbTypes->setCurrentIndex(m_typeIndex);

  m_lengthSelection = new QWidget;
  m_flagSelection = new QWidget;

  m_spnLength = new QSpinBox(this);
  m_spnLength->setMinimum(1);
  m_spnLength->setValue(static_cast<int>(m_length));

  m_spnFlag = new QSpinBox(this);
  m_spnFlag->setMinimum(1);
  m_spnFlag->setMaximum(0xFF);
  m_spnFlag->setValue(m_flagValue);

  connect(m_cmbTypes, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          &DlgChangeType::onTypeChange);
}

void DlgChangeType::makeLayouts()
{
  QLabel* lblType = new QLabel(tr("New type: "), this);
  QLabel* lblLength = new QLabel(tr("Length: "), this);
  QLabel* lblFlag = new QLabel(tr("Flag: "), this);

  QWidget* typeSelection = new QWidget(this);
  QHBoxLayout* typeSelectionLayout = new QHBoxLayout;
  typeSelectionLayout->addWidget(lblType);
  typeSelectionLayout->addWidget(m_cmbTypes);
  typeSelection->setLayout(typeSelectionLayout);

  QHBoxLayout* lengthSelectionLayout = new QHBoxLayout;
  lengthSelectionLayout->addWidget(lblLength);
  lengthSelectionLayout->addWidget(m_spnLength);
  m_lengthSelection->setLayout(lengthSelectionLayout);

  QHBoxLayout* flagSelectionLayout = new QHBoxLayout;
  flagSelectionLayout->addWidget(lblFlag);
  flagSelectionLayout->addWidget(m_spnFlag);
  m_flagSelection->setLayout(flagSelectionLayout);

  Common::MemType theType = static_cast<Common::MemType>(m_typeIndex);
  if (theType != Common::MemType::type_string && theType != Common::MemType::type_byteArray)
    m_lengthSelection->hide();
  if (theType != Common::MemType::type_flag)
    m_flagSelection->hide();

  QDialogButtonBox* buttonBox =
      new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
  connect(buttonBox, &QDialogButtonBox::accepted, this, &DlgChangeType::accept);
  connect(buttonBox, &QDialogButtonBox::rejected, this, &DlgChangeType::reject);

  QVBoxLayout* main_layout = new QVBoxLayout;

  main_layout->addWidget(typeSelection);
  main_layout->addWidget(m_lengthSelection);
  main_layout->addWidget(m_flagSelection);
  main_layout->addWidget(buttonBox);
  main_layout->setSpacing(1);
  setLayout(main_layout);
}

int DlgChangeType::getTypeIndex() const
{
  return m_typeIndex;
}

size_t DlgChangeType::getLength() const
{
  return m_length;
}

u8 DlgChangeType::getFlagValue() const
{
  return m_flagValue;
}

void DlgChangeType::accept()
{
  m_typeIndex = m_cmbTypes->currentIndex();
  m_length = m_spnLength->value();
  m_flagValue = m_spnFlag->value();

  setResult(QDialog::Accepted);
  hide();
}

void DlgChangeType::onTypeChange(int index)
{
  Common::MemType theType = static_cast<Common::MemType>(index);
  if (theType == Common::MemType::type_string || theType == Common::MemType::type_byteArray)
    m_lengthSelection->show();
  else
    m_lengthSelection->hide();
  if (theType == Common::MemType::type_flag)
    m_flagSelection->show();
  else
    m_flagSelection->hide();
  adjustSize();
}
