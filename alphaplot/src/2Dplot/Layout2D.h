#ifndef LAYOUT2D_H
#define LAYOUT2D_H

#include "MyWidget.h"
#include "AxisRect2D.h"
#include "Plot2D.h"

#include <QHBoxLayout>
#include <QPushButton>

#include "future/core/column/Column.h"
#include "StatBox2D.h"
class QLabel;
class Table;
class AxisRect2D;
class LayoutGrid2D;
class LayoutButton2D;

class Layout2D : public MyWidget {
  Q_OBJECT

 public:
  Layout2D(const QString &label, QWidget *parent = nullptr,
           const QString name = QString(), Qt::WindowFlags f = Qt::Widget);
  ~Layout2D();

  StatBox2D::BoxWhiskerData generateBoxWhiskerData(Column *data, int from,
                                                   int to, int key);

  void generateFunction2DPlot(QVector<double> *xdata, QVector<double> *ydata,
                              const QString xLabel, const QString yLabel);
  void generateScatter2DPlot(Column *xData, Column *yData, int from, int to);
  void generateStatBox2DPlot(Table *table, QList<Column *> ycollist, int from,
                             int to, int key);
  void generateHistogram2DPlot(const AxisRect2D::BarType &barType,
                               bool multilayout, Table *table,
                               QList<Column *> collist, int from, int to);

  void generateLineSpecial2DPlot(
      const AxisRect2D::LineScatterSpecialType &plotType, Table *table,
      Column *xData, Column *yData, int from, int to);
  void generateCurve2DPlot(const AxisRect2D::LineScatterType &plotType,
                           Table *table, Column *xcol, Column *ycol, int from,
                           int to);
  void generateBar2DPlot(const AxisRect2D::BarType &barType, Table *table,
                         Column *xData, Column *yData, int from, int to);
  void generateVector2DPlot(const Vector2D::VectorPlot &vectorplot,
                            Table *table, Column *x1Data, Column *y1Data,
                            Column *x2Data, Column *y2Data, int from, int to);
  void generatePie2DPlot(Table *table, Column *xData, int from, int to);

  QList<AxisRect2D *> getAxisRectList();
  AxisRect2D *getSelectedAxisRect(int col, int row);
  int getAxisRectIndex(AxisRect2D *axisRect2d);
  AxisRect2D *getCurrentAxisRect();
  Plot2D *getPlotCanwas() const;

  void setLayoutDimension(QPair<int, int> dimension);
  void removeAxisRect(int index);

  int getLayoutRectGridIndex(QPair<int, int> coord);
  QPair<int, int> getLayoutRectGridCoordinate(int index);
  LayoutButton2D *addLayoutButton(int num);
  void setBackground(const QColor &background);
  void setGraphTool(const Graph2DCommon::Picker &picker);
  void print();

 private slots:
  AxisRect2D *addAxisRectItem();
  AxisRect2D *addAxisRectItem(const AlphaPlot::ColumnDataType &xcoldatatype,
                              const AlphaPlot::ColumnDataType &ycoldatatype);
  void removeAxisRectItem();
  void axisRectSetFocus(AxisRect2D *rect);
  void activateLayout(LayoutButton2D *button);
  void showtooltip(QPointF position, double xval, double yval);

 private:
  void addTextToAxisTicker(Column *col, Axis2D *axis);

 private:
  QWidget *main_widget_;
  Plot2D *plot2dCanvas_;

  LayoutGrid2D *layout_;
  QPair<int, int> layoutDimension_;
  QList<LayoutButton2D *> buttionlist_;

  QHBoxLayout *layoutButtonsBox_;
  QHBoxLayout *layoutManagebuttonsBox_;
  QPushButton *addLayoutButton_;
  QPushButton *removeLayoutButton_;
  QLabel *streachLabel_;

  AxisRect2D *currentAxisRect_;
  Graph2DCommon::Picker picker_;

 private slots:
  void mouseMoveSignal(QMouseEvent *event);
  void mousePressSignal(QMouseEvent *event);
  void mouseReleaseSignal(QMouseEvent *event);
  void mouseWheel();
  void beforeReplot();
  void refresh();
  bool exportGraph();
  void exportPDF(const QString &filename);
  void printGraph();

 signals:
  void AxisRectCreated(AxisRect2D *, MyWidget *);
  void AxisRectRemoved(MyWidget *);
};

#endif  // LAYOUT2D_H