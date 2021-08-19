// --------------------------------------------------------------------------
//                   OpenMS -- Open-Source Mass Spectrometry
// --------------------------------------------------------------------------
// Copyright The OpenMS Team -- Eberhard Karls University Tuebingen,
// ETH Zurich, and Freie Universitaet Berlin 2002-2021.
//
// This software is released under a three-clause BSD license:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of any author or any participating institution
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
// For a full list of authors, refer to the file AUTHORS.
// --------------------------------------------------------------------------
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL ANY OF THE AUTHORS OR THE CONTRIBUTING
// INSTITUTIONS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// --------------------------------------------------------------------------
// $Maintainer: Julianus Pfeuffer $
// $Authors: Dhanmoni Nath, Julianus Pfeuffer $
// --------------------------------------------------------------------------

#ifdef QT_WEBENGINEWIDGETS_LIB
#include <OpenMS/VISUAL/SequenceVisualizer.h>
#include <ui_SequenceVisualizer.h>

#include <QWebChannel>
#include <QString>

#include <QtWebEngineWidgets/QWebEngineView>

// This is the window that appears when we click on 'show' in the 'sequence' column of the protein table

namespace OpenMS
{
  SequenceVisualizer::SequenceVisualizer(QWidget* parent) :
      QWidget(parent), ui(new Ui::SequenceVisualizer)
  {
    ui->setupUi(this);
    auto* view = new QWebEngineView(parent);
    auto* channel = new QWebChannel(this); // setup Qt WebChannel API
    view->page()->setWebChannel(channel);
    channel->registerObject(QString("SequenceVisualizer"), this); // This object will be available in HTML file.
    view->load(QUrl("qrc:/new/sequence_viz.html"));
    ui->gridLayout->addWidget(view);
  }

  SequenceVisualizer::~SequenceVisualizer()
  {
    delete ui;
  }

  // Get protein and peptide data from the protein table and store inside the m_json_data_obj object. 
  // Inside the HTML file, this QObject will be available and we'll access these protein and 
  // peptide data using the qtWebEngine and webChannel API.
  void SequenceVisualizer::setProteinPeptideDataToJsonObj(const QString& accession_num,
      const QString& pro_seq,
      const QJsonArray& pep_data)
  {
    m_json_data_obj["accession_num"] = accession_num;
    m_json_data_obj["protein_sequence_data"] = pro_seq;
    m_json_data_obj["peptides_data"] = pep_data;
  }
}// namespace OpenMS
#endif