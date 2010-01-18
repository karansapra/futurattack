using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace QuickHull2D
{    
    public partial class main_window : Form
    {
        const uint NPOINTS = 64;

        Vector2[] points = new Vector2[NPOINTS];
        List<Vector2> point_set = new List<Vector2>((int)NPOINTS);
        List<Edge> hull = new List<Edge>();

        public main_window()
        {
            InitializeComponent();
        }


        private void generate_Click(object sender, EventArgs e)
        {
            Random rnd = new Random();
            Graphics g = canvas.CreateGraphics();
            g.Clear(Color.Black);
            point_set.Clear();
            for (uint i = 0; i < NPOINTS; i++)
            {
                points[i] = new Vector2((float)rnd.NextDouble()*canvas.Width*0.80f+10, (float)rnd.NextDouble()*canvas.Height*0.8f+10);
                g.DrawEllipse(Pens.White, points[i].x - 1, points[i].y - 1, 3, 3);
                point_set.Add(points[i]);
            }
            
            qhull.Enabled = true;
        }

        private void ComputeHullIter()
        {            
            bool continue_computation = true;

            while (continue_computation)
            {
                continue_computation = false;
                List<Edge> temp_hull = new List<Edge>();

                foreach (Edge edge in hull)
                {
                    Vector2 N = edge.GetNormal();
                    Vector2 new_v = new Vector2();
                    float threshold = 0.0f;

                    foreach (Vector2 v in point_set)
                    {
                        float scalar_prod = N * (v - edge.A);
                        if (scalar_prod < threshold)
                        {
                            threshold = scalar_prod;
                            new_v = v;
                        }
                    }

                    if (threshold == 0.0f)
                    {
                        temp_hull.Add(edge);
                    }
                    else
                    {
                        continue_computation = true;

                        Edge edgeA = new Edge();
                        edgeA.A = edge.A;
                        edgeA.B = new_v;

                        Edge edgeB = new Edge();
                        edgeB.A = new_v;
                        edgeB.B = edge.B;

                        temp_hull.Add(edgeA);
                        temp_hull.Add(edgeB);
                    }
                }

                hull = temp_hull;
            }
        }

        private void ComputeHull()
        {
            Vector2 max_x = point_set[0];
            Vector2 max_y = point_set[0];
            Vector2 min_x = point_set[0];
            Vector2 min_y = point_set[0];

            hull.Clear();

            //Initial search
            foreach (Vector2 v in point_set)
            {
                if (v.x > max_x.x)
                    max_x = v;
                if (v.y > max_y.y)
                    max_y = v;
                if (v.x < min_x.x)
                    min_x = v;
                if (v.y < min_y.y)
                    min_y = v;
            }

            Edge edgeA = new Edge();
            Edge edgeB = new Edge();
            Edge edgeC = new Edge();
            Edge edgeD = new Edge();

            edgeA.A = min_x;
            edgeA.B = min_y;
            if (edgeA.Length2() != 0.0f)
                hull.Add(edgeA);

            edgeB.A = min_y;
            edgeB.B = max_x;
            if (edgeB.Length2() != 0.0f)
                hull.Add(edgeB);
            
            edgeC.A = max_x;
            edgeC.B = max_y;
            if (edgeC.Length2() != 0.0f)
                hull.Add(edgeC);

            edgeD.A = max_y;
            edgeD.B = min_x;
            if (edgeD.Length2() != 0.0f)
                hull.Add(edgeD);

            
            ComputeHullIter();
        }

        private void qhull_Click(object sender, EventArgs e)
        {

            Graphics g = canvas.CreateGraphics();

            ComputeHull();

            foreach (Edge edge in hull)
            {
                g.DrawLine(Pens.GreenYellow, edge.A.x, edge.A.y, edge.B.x, edge.B.y);
            }
        }
    }
}
