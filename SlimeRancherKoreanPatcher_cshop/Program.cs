using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace SlimeRancherKoreanPatcher_cshop
{
    class Program
    {
        static string currentDirectory;
        static string SlimeFolderPath;
        static string[] findResFileName = { "achieve", "actor", "exchange", "global", "keys", "mail", "pedia", "range", "tutorial", "ui" };
        static int[] findResFileNum = { 2, 1, 3, 0, 1, 0, 2, 4, 1, 1 };
        static string[] findSharedFileName = { "OpenSans-Semibold SDF Material", "OpenSans SDF Atlas", "TMP_SDF-Mobile" };
        static int[] findSharedFileNum = { 0, 0, 0 };
        static string[] findGlobalFileName = { "TMP_FontAsset" };
        static int[] findGlobalFileNum = { 0 };

        static void Main(string[] args)
        {
            SlimeFolderPath = args[0];
            Console.WriteLine(SlimeFolderPath);
            currentDirectory = System.IO.Directory.GetCurrentDirectory();
            SlimeRancherKoreanPatcher_managedCpp.ManagedPatcherWarp managedPatcher =
                new SlimeRancherKoreanPatcher_managedCpp.ManagedPatcherWarp(SlimeFolderPath, currentDirectory);

            SlimeRancherKoreanPatcher_managedCpp.myAssetFileInfo[] temp;
            
            DownloadCSV();
            temp = managedPatcher.FindAssetOffs(
                findResFileName, findResFileNum,
                findSharedFileName, findSharedFileNum,
                findGlobalFileName, findGlobalFileNum);

            
            Console.WriteLine("Press any key to exit");
            Console.Read();
        }

        static void DownloadCSV()
        {
            
            string CSVURLString = System.IO.File.ReadAllText(@"CSVURL.txt");
            CSVURLString = CSVURLString.Replace("\r", "");
            string[] CSVURL = CSVURLString.Split('\n');
            List<string[]> ListCSVURL = new List<string[]>();
            for (int i = 0; i < CSVURL.Length; i++)
            {
                ListCSVURL.Add(CSVURL[i].Split('\\'));
            }
            string tempFolder = @"temp";
            CreateFolderOrClean(tempFolder);  

            for (int i = 0; i < ListCSVURL.Count; i++)
            {
                WebClient webClient = new WebClient();
                webClient.DownloadFile(ListCSVURL[i][1], tempFolder + "\\" + ListCSVURL[i][0] + ".csv");
            }
        }

        static void CreateFolderOrClean(string folderName)
        {
            DirectoryInfo di = new DirectoryInfo(folderName);
            if (di.Exists == false)
            {
                di.Create();
            }
            else
            {
                Directory.Delete(folderName, true);
                di.Create();
            }
        }
    }
}
