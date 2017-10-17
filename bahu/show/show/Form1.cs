using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace show
{
    public partial class Form1 : Form
    {
        public string keyAddress = "E:\\data\\bahu\\key\\key.txt";
        public string relationAddress = "E:\\data\\bahu\\relation\\relation.txt";
        public List<string> keys = new List<string>();
        public double[,] relation;

        public Form1()
        {
            InitializeComponent();
            //读取key.
            StreamReader rd = new StreamReader(keyAddress, Encoding.GetEncoding("gb2312"));
            string s = rd.ReadLine();
            while (s != null)
            {
                keys.Add(s);
                s = rd.ReadLine();
            }
            //for (int i = 0; i < keys.Count; i++)
            //{
            //    textBox_out.Text += keys[i];
            //}
            relation = new double[keys.Count, keys.Count];
            rd = new StreamReader(relationAddress);
            for (int i = 0; i < keys.Count; i++)
            {
                string line = rd.ReadLine();
                string[] data = line.Split(' ');
                for (int j = 0; j < keys.Count; j++)
                {
                    relation[i, j] = double.Parse(data[j]);
                    //textBox_out.Text = relation[i, j].ToString();
                }
            }
        }

        private void button_search_Click(object sender, EventArgs e)
        {
            //读入用户输入，并转化为索引.
            List<int> keysIndex = new List<int>();
            textBox_out.Text = "";
            string textIn = textBox_in.Text;
            string[] keysIn = textIn.Split(';');
            for (int i = 0; i < keysIn.Length; i++)
            {
                for (int j = 0; j < keys.Count; j++)
                {
                    if (keys[j] == keysIn[i])
                        keysIndex.Add(j);
                }
               // textBox_out.Text += relation[5, keysIndex[i]].ToString("E")+"\n";
            }
            //计算输入与所有的差异.
            double[] difference = new double[keys.Count];
            for (int i = 0; i < keys.Count; i++)
            {
                difference[i] = 0;
            }
            for (int i = 0; i < keysIndex.Count; i++)
            {
                for (int j = 0; j < keys.Count; j++)
                {
                    difference[j] += relation[keysIndex[i], j];
                }
            }
            //排序.
            double[] old_difference = new double[keys.Count];
            for (int i = 0; i < keys.Count; i++)
                old_difference[i]=difference[i];
            for (int i = 0; i < keys.Count; i++)
            {
                for (int j = 0; j < keys.Count-1; j++)
                {
                    if (difference[j] > difference[j + 1])
                    {
                        double temp = difference[j];
                        difference[j] = difference[j + 1];
                        difference[j + 1] = temp;
                    }
                }
            }
            //输出最小差对应的名字.
            for (int i = 0; i < 10; i++)
            {
                for (int j = 0; j < keys.Count; j++)
                {
                    if(difference[i]==old_difference[j])
                        textBox_out.Text += keys[j] + ";";
                }
            }
        }
    }
}
