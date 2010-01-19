using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using SharpGL;

namespace TornadoEngineTools
{
    public partial class main_window : Form
    {
        List<Vector3> vertex_data = new List<Vector3>();

        public main_window()
        {
            InitializeComponent();            
        }

        private void button1_Click(object sender, EventArgs e)
        {
            openGLCtrl2.Refresh();
        }

        private float angle = 0.0f;

        private void openGLCtrl2_OpenGLDraw(object sender, PaintEventArgs e)
        {
            OpenGL ogl = this.openGLCtrl2.OpenGL;
            ogl.ClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            ogl.Clear(OpenGL.COLOR_BUFFER_BIT | OpenGL.DEPTH_BUFFER_BIT);
            
            ogl.LoadIdentity();
            ogl.LookAt(0.0, 1.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            ogl.Rotate(0.0f, angle, 0.0f);
            angle += 2.0f;

            ogl.Begin(OpenGL.POINTS);
            ogl.Color(1.0, 1.0, 1.0);
            foreach (Vector3 v in vertex_data)
            {
                ogl.Vertex(v.x, v.y, v.z);
            }
            ogl.End();

            ogl.LoadIdentity();
        }

        private void openGLCtrl2_Load(object sender, EventArgs e)
        {
        }

        private void chargerModèleWavefrontOBJToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (file_open.ShowDialog() != DialogResult.OK)
                return;

            ModelLoader m3d = new OBJLoader();
            if (m3d.Load(file_open.FileName) != ModelLoaderError.ERROR_OK)
                return;
            
            ModelStats ms = m3d.GetStats();
            if (ms.Nvertex == 0)
                return;

            vertex_data = m3d.GetVertex();

            vertexcountlabel.Text = "Nombre de vertex:" + ms.Nvertex.ToString();
        }

        private void aProposToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Tornado Engine Mesh Tool\nCopyright 2010\nClément JACOB", "A Propos",MessageBoxButtons.OK,MessageBoxIcon.Information);
        }

        private void toolStripStatusLabel1_Click(object sender, EventArgs e)
        {

        }

        private void sauvegarderLeMeshPourTornadoEngineTEMToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void openGLCtrl2_MouseEnter(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = "Zone d'affichage OpenGL du modèle chargé";
        }

        private void main_window_MouseEnter(object sender, EventArgs e)
        {
            
        }
    }
}
