using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace TornadoEngineTools
{
    enum ModelLoaderError {ERROR_OK, ERROR_FILE_NOT_EXIST, ERROR_FORMAT_NOT_RECOGNIZED};

    struct ModelStats
    {
        public uint Nvertex;
    }

    interface ModelLoader
    {
        ModelLoaderError Load(string file);
        ModelStats GetStats();
        List<Vector3> GetVertex();
    }

    class OBJLoader : ModelLoader
    {
        private List<Vector3> vertex_data = new List<Vector3>();

        private void parse_line(string line)
        {
            line = line.Replace('.', ',');
            string[] ops = line.Split(' ');
            
            if (ops.Length == 0)
                return;

            switch (ops[0])
            {
                case "v":
                    if (ops.Length < 4)
                        return;
                                       
                    vertex_data.Add(new Vector3(
                        float.Parse(ops[1]),
                        float.Parse(ops[2]),
                        float.Parse(ops[3])
                        ));

                    break;
                default:
                    break;
            }
        }

        ModelStats ModelLoader.GetStats()
        {
            ModelStats ms;
            ms.Nvertex = (uint)vertex_data.Count;
            return ms;
        }

        ModelLoaderError ModelLoader.Load(string file)
        {
            System.IO.StreamReader f;
            try
            {
                f = new System.IO.StreamReader(file);
            }
            catch
            {
                return ModelLoaderError.ERROR_FILE_NOT_EXIST;
            }

            string line;
            while (!f.EndOfStream)
            {
                line = f.ReadLine();
                parse_line(line);
            }
            

            f.Close();

            return ModelLoaderError.ERROR_OK;
        }

        List<Vector3> ModelLoader.GetVertex()
        {
            return vertex_data;
        }
    }
}
