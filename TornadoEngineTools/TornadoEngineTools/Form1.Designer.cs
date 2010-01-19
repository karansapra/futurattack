namespace TornadoEngineTools
{
    partial class main_window
    {
        /// <summary>
        /// Variable nécessaire au concepteur.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Nettoyage des ressources utilisées.
        /// </summary>
        /// <param name="disposing">true si les ressources managées doivent être supprimées ; sinon, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Code généré par le Concepteur Windows Form

        /// <summary>
        /// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
        /// le contenu de cette méthode avec l'éditeur de code.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(main_window));
            this.openGLCtrl2 = new SharpGL.OpenGLCtrl();
            this.menu = new System.Windows.Forms.MenuStrip();
            this.fichierToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.chargerModèleWavefrontOBJToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.file_open = new System.Windows.Forms.OpenFileDialog();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.aideToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aProposToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.sauvegarderLeMeshPourTornadoEngineTEMToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.vertexcountlabel = new System.Windows.Forms.Label();
            this.menu.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // openGLCtrl2
            // 
            this.openGLCtrl2.DrawRenderTime = false;
            this.openGLCtrl2.FrameRate = 50F;
            this.openGLCtrl2.GDIEnabled = false;
            this.openGLCtrl2.Location = new System.Drawing.Point(12, 27);
            this.openGLCtrl2.Name = "openGLCtrl2";
            this.openGLCtrl2.Size = new System.Drawing.Size(513, 407);
            this.openGLCtrl2.TabIndex = 0;
            this.openGLCtrl2.Load += new System.EventHandler(this.openGLCtrl2_Load);
            this.openGLCtrl2.OpenGLDraw += new System.Windows.Forms.PaintEventHandler(this.openGLCtrl2_OpenGLDraw);
            this.openGLCtrl2.MouseEnter += new System.EventHandler(this.openGLCtrl2_MouseEnter);
            // 
            // menu
            // 
            this.menu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fichierToolStripMenuItem,
            this.toolStripMenuItem1});
            this.menu.Location = new System.Drawing.Point(0, 0);
            this.menu.Name = "menu";
            this.menu.Size = new System.Drawing.Size(696, 24);
            this.menu.TabIndex = 1;
            this.menu.Text = "menuStrip1";
            // 
            // fichierToolStripMenuItem
            // 
            this.fichierToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.chargerModèleWavefrontOBJToolStripMenuItem,
            this.sauvegarderLeMeshPourTornadoEngineTEMToolStripMenuItem});
            this.fichierToolStripMenuItem.Name = "fichierToolStripMenuItem";
            this.fichierToolStripMenuItem.Size = new System.Drawing.Size(54, 20);
            this.fichierToolStripMenuItem.Text = "Fichier";
            // 
            // chargerModèleWavefrontOBJToolStripMenuItem
            // 
            this.chargerModèleWavefrontOBJToolStripMenuItem.Name = "chargerModèleWavefrontOBJToolStripMenuItem";
            this.chargerModèleWavefrontOBJToolStripMenuItem.Size = new System.Drawing.Size(336, 22);
            this.chargerModèleWavefrontOBJToolStripMenuItem.Text = "Charger modèle Wavefront (.OBJ)";
            this.chargerModèleWavefrontOBJToolStripMenuItem.Click += new System.EventHandler(this.chargerModèleWavefrontOBJToolStripMenuItem_Click);
            // 
            // file_open
            // 
            this.file_open.DefaultExt = "*.OBJ";
            this.file_open.Filter = "Modèle 3D Wavefront|*.OBJ";
            this.file_open.InitialDirectory = "C:\\";
            // 
            // groupBox1
            // 
            this.groupBox1.Location = new System.Drawing.Point(532, 28);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(152, 246);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Paramètres de création";
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.aideToolStripMenuItem,
            this.aProposToolStripMenuItem});
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(24, 20);
            this.toolStripMenuItem1.Text = "?";
            // 
            // aideToolStripMenuItem
            // 
            this.aideToolStripMenuItem.Name = "aideToolStripMenuItem";
            this.aideToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.aideToolStripMenuItem.Text = "Aide";
            // 
            // aProposToolStripMenuItem
            // 
            this.aProposToolStripMenuItem.Name = "aProposToolStripMenuItem";
            this.aProposToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.aProposToolStripMenuItem.Text = "A Propos";
            this.aProposToolStripMenuItem.Click += new System.EventHandler(this.aProposToolStripMenuItem_Click);
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1});
            this.statusStrip1.Location = new System.Drawing.Point(0, 446);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(696, 22);
            this.statusStrip1.TabIndex = 3;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(10, 17);
            this.toolStripStatusLabel1.Text = " ";
            this.toolStripStatusLabel1.Click += new System.EventHandler(this.toolStripStatusLabel1_Click);
            // 
            // sauvegarderLeMeshPourTornadoEngineTEMToolStripMenuItem
            // 
            this.sauvegarderLeMeshPourTornadoEngineTEMToolStripMenuItem.Enabled = false;
            this.sauvegarderLeMeshPourTornadoEngineTEMToolStripMenuItem.Name = "sauvegarderLeMeshPourTornadoEngineTEMToolStripMenuItem";
            this.sauvegarderLeMeshPourTornadoEngineTEMToolStripMenuItem.Size = new System.Drawing.Size(336, 22);
            this.sauvegarderLeMeshPourTornadoEngineTEMToolStripMenuItem.Text = "Sauvegarder le mesh pour Tornado Engine (.TEM)";
            this.sauvegarderLeMeshPourTornadoEngineTEMToolStripMenuItem.Click += new System.EventHandler(this.sauvegarderLeMeshPourTornadoEngineTEMToolStripMenuItem_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.vertexcountlabel);
            this.groupBox2.Location = new System.Drawing.Point(532, 280);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(152, 154);
            this.groupBox2.TabIndex = 3;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Statistiques";
            // 
            // vertexcountlabel
            // 
            this.vertexcountlabel.AutoSize = true;
            this.vertexcountlabel.Location = new System.Drawing.Point(7, 20);
            this.vertexcountlabel.Name = "vertexcountlabel";
            this.vertexcountlabel.Size = new System.Drawing.Size(100, 13);
            this.vertexcountlabel.TabIndex = 0;
            this.vertexcountlabel.Text = "Nombre de vertex:0";
            // 
            // main_window
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(696, 468);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.openGLCtrl2);
            this.Controls.Add(this.menu);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menu;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "main_window";
            this.Text = "Tornado Engine - Mesh Tool";
            this.MouseEnter += new System.EventHandler(this.main_window_MouseEnter);
            this.menu.ResumeLayout(false);
            this.menu.PerformLayout();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private SharpGL.OpenGLCtrl openGLCtrl2;
        private System.Windows.Forms.MenuStrip menu;
        private System.Windows.Forms.ToolStripMenuItem fichierToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem chargerModèleWavefrontOBJToolStripMenuItem;
        private System.Windows.Forms.OpenFileDialog file_open;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem aideToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aProposToolStripMenuItem;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.ToolStripMenuItem sauvegarderLeMeshPourTornadoEngineTEMToolStripMenuItem;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label vertexcountlabel;
    }
}

