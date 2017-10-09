using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace sharedassets0Editor
{
    class Program
    {
        static void Main(string[] args)
        {
            string FileIDFileName = @"FileID.txt";
            string MonoFileIDFileName = @"MonoFileID.txt";
            string FileIDString = System.IO.File.ReadAllText(FileIDFileName);
            string MonoFileIDString = System.IO.File.ReadAllText(MonoFileIDFileName);

            string[] assetFileNames = { "OpenSans-Semibold SDF Material", "OpenSans SDF Atlas", "TMP_SDF-Mobile", "TMP_FontAsset", "MonoBehaviour OpenSans SDF"};
            FileIDString = FileIDString.Replace("\r", "");
            string[] splitedFileID = FileIDString.Split('\n');

            int[] FileID = new int[assetFileNames.Length];

            for (int i=0; i< assetFileNames.Length-1; i++)
            {
                int j = 0;
                int ID = 0;
                for (j = 0; j < splitedFileID.Length; j++)
                {
                    string[] tempFileID = splitedFileID[j].Split(':');
                    if(assetFileNames[i] == tempFileID[0])
                    {
                        ID = int.Parse(tempFileID[1]);
                        break;
                    }
                }
                if (ID == 0)
                {
                    throw new Exception("Cannot Find FileID");
                }
                FileID[i] = ID;
            }
            FileID[FileID.Length - 1] = int.Parse(MonoFileIDString);


            byte[] byteTMP_SDF = BitConverter.GetBytes(FileID[2]); // TMP_SDF-Mobile
            byte[] byteMaterial = BitConverter.GetBytes(FileID[0]);
            byte[] byteAtlas = BitConverter.GetBytes(FileID[1]);
            byte[] byteTMP_FontAsset = BitConverter.GetBytes(FileID[3]);
            byte[] byteMonoBehaviour = BitConverter.GetBytes(FileID[4]);

            
            DirectoryInfo di = new DirectoryInfo(@"..\sharedassets0_patch");
            if (di.Exists == false)
            {
                di.Create();
            }
            else
            {
                Directory.Delete(@"..\sharedassets0_patch", true);
                di.Create();
            }

            File.Copy(@"sharedassets0\OpenSans-Semibold SDF Material.dat", @"..\sharedassets0_patch\Raw_0_" + FileID[0] + ".dat", true);
            using (FileStream fsMaterial = new FileStream(@"..\sharedassets0_patch\Raw_0_" + FileID[0] + ".dat", FileMode.Open, FileAccess.ReadWrite))
            {
                fsMaterial.Seek(0x00000028, SeekOrigin.Begin);
                for (int i = 0; i < 4; i++)
                {
                    fsMaterial.WriteByte(byteTMP_SDF[i]);
                }
                fsMaterial.Seek(0x00000060, SeekOrigin.Begin);
                for (int i = 0; i < 4; i++)
                {
                    fsMaterial.WriteByte(byteAtlas[i]);
                }
            }

            File.Copy(@"sharedassets0\MonoBehaviour OpenSans SDF.dat", @"..\sharedassets0_patch\Raw_0_" + FileID[4] + ".dat", true);
            using (FileStream fsMonoBehaviour = new FileStream(@"..\sharedassets0_patch\Raw_0_" + FileID[4] + ".dat", FileMode.Open, FileAccess.ReadWrite))
            {
                fsMonoBehaviour.Seek(0x00000014, SeekOrigin.Begin);
                for (int i = 0; i < 4; i++)
                {
                    fsMonoBehaviour.WriteByte(byteTMP_FontAsset[i]);
                }
                fsMonoBehaviour.Seek(0x00000034, SeekOrigin.Begin);
                for (int i = 0; i < 4; i++)
                {
                    fsMonoBehaviour.WriteByte(byteMaterial[i]);
                }
                fsMonoBehaviour.Seek(0x000000A4, SeekOrigin.Begin);
                for (int i = 0; i < 4; i++)
                {
                    fsMonoBehaviour.WriteByte(byteAtlas[i]);
                }
            }

            File.Copy(@"sharedassets0\OpenSans SDF Atlas.dat", @"..\sharedassets0_patch\Raw_0_" + FileID[1] + ".dat", true);

            string sharedassets0_patch_list = "sharedassets0_patch\\Raw_0_" + FileID[0] + ".dat\r\n" +
                "sharedassets0_patch\\Raw_0_" + FileID[1] + ".dat\r\n" +
                "sharedassets0_patch\\Raw_0_" + FileID[4] + ".dat";

            System.IO.File.WriteAllText(@"..\sharedassets0_patch\sharedassets0_patch_list.txt", sharedassets0_patch_list);
        }
    }
}
