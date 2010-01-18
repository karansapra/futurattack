namespace QuickHull2D
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
            this.canvas = new System.Windows.Forms.Panel();
            this.qhull = new System.Windows.Forms.Button();
            this.generate = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // canvas
            // 
            this.canvas.BackColor = System.Drawing.Color.Black;
            this.canvas.Location = new System.Drawing.Point(13, 13);
            this.canvas.Name = "canvas";
            this.canvas.Size = new System.Drawing.Size(444, 360);
            this.canvas.TabIndex = 0;
            // 
            // qhull
            // 
            this.qhull.Enabled = false;
            this.qhull.Location = new System.Drawing.Point(463, 72);
            this.qhull.Name = "qhull";
            this.qhull.Size = new System.Drawing.Size(75, 53);
            this.qhull.TabIndex = 1;
            this.qhull.Text = "Compute QuickHull";
            this.qhull.UseVisualStyleBackColor = true;
            this.qhull.Click += new System.EventHandler(this.qhull_Click);
            // 
            // generate
            // 
            this.generate.Location = new System.Drawing.Point(463, 13);
            this.generate.Name = "generate";
            this.generate.Size = new System.Drawing.Size(75, 53);
            this.generate.TabIndex = 2;
            this.generate.Text = "Points generation";
            this.generate.UseVisualStyleBackColor = true;
            this.generate.Click += new System.EventHandler(this.generate_Click);
            // 
            // main_window
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(549, 385);
            this.Controls.Add(this.generate);
            this.Controls.Add(this.qhull);
            this.Controls.Add(this.canvas);
            this.Name = "main_window";
            this.Text = "QuickHull2D - C.Jacob";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel canvas;
        private System.Windows.Forms.Button qhull;
        private System.Windows.Forms.Button generate;
    }
}

