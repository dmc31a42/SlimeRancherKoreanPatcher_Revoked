using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Net;

namespace TextDatExtract
{
    class Program
    {
        static string SlimeFolderPath = "";
        static string DropboxFolderPath = "";
        static string help = "SlimeRancherModMaker.exe -Patch(or -Update, -Auto) \"SlimeRancherFolderPath\" (\"DropboxFolderPath\")";
        static void Main(string[] args)
        {
            SlimeFolderPath = args[1];
            if(args.Length == 3)
            {
                DropboxFolderPath = args[2];
            }
            switch(args[0])
            {
                case "-Patch":
                    {
                        PatchWork();
                          
                    }
                    break;
                case "-Update":
                    {
                        UpdateWork();
                    }
                    break;
                case "-Auto":
                    {
                        UpdateWork();
                        PatchWork();
                        System.Timers.Timer createAndUpdateTimer = new System.Timers.Timer(10 * 60 * 1000);
                        createAndUpdateTimer.Elapsed += CreateAndUpdateTimer_Elapsed;
                        createAndUpdateTimer.Start();
                        Console.WriteLine("Create And Update Timer on!");
                        Console.WriteLine("Press Any key to Exit");
                        Console.ReadKey();
                    }
                    break;
                case "-TEST":
                    {
                        {
                            string currentDirectory = System.IO.Directory.GetCurrentDirectory();
                            System.Diagnostics.Process ps = new System.Diagnostics.Process();
                            ps.StartInfo.FileName = currentDirectory + @"\sharedassets0Editor.exe";
                            ps.StartInfo.WorkingDirectory = currentDirectory;
                            ps.Start();
                            ps.WaitForExit();
                        }
                    }
                    break;
                default:
                    Console.WriteLine(help);
                    return;
            }

            
        }

        private static void CreateAndUpdateTimer_Elapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            UpdateWork();
            PatchWork();
        }

        public static void CopyFolder(string sourceFolder, string destFolder)
        {
            if (!Directory.Exists(destFolder))
                Directory.CreateDirectory(destFolder);

            string[] files = Directory.GetFiles(sourceFolder);
            string[] folders = Directory.GetDirectories(sourceFolder);

            foreach (string file in files)
            {
                string name = Path.GetFileName(file);
                string dest = Path.Combine(destFolder, name);
                try
                {
                    File.Copy(file, dest, true);
                }
                catch (Exception e)
                {
                    Console.WriteLine(e.ToString());
                }
            }

            // foreach 안에서 재귀 함수를 통해서 폴더 복사 및 파일 복사 진행 완료  
            foreach (string folder in folders)
            {
                string name = Path.GetFileName(folder);
                string dest = Path.Combine(destFolder, name);
                CopyFolder(folder, dest);
            }
        }

        static void PatchWork()
        {
            string currentDirectory = System.IO.Directory.GetCurrentDirectory();
            string CSVURLString = System.IO.File.ReadAllText(@"CSVURL.txt");
            CSVURLString = CSVURLString.Replace("\r", "");
            string[] CSVURL = CSVURLString.Split('\n');
            List<string[]> ListCSVURL = new List<string[]>();
            for (int i = 0; i < CSVURL.Length; i++)
            {
                ListCSVURL.Add(CSVURL[i].Split('\\'));
            }
            string tempFolder = @"temp";
            {
                DirectoryInfo di = new DirectoryInfo(tempFolder);
                if (di.Exists == false)
                {
                    di.Create();
                }
                else
                {
                    Directory.Delete(tempFolder, true);
                    di.Create();
                }
            }

            string[] findResFileName = { "achieve", "actor", "exchange", "global", "keys", "mail", "pedia", "range", "tutorial", "ui" };
            int[] findResFileNum = { 2, 1, 3, 0, 1, 0, 2, 4, 1, 1 };

            for (int i = 0; i < ListCSVURL.Count; i++)
            {
                WebClient webClient = new WebClient();
                webClient.DownloadFile(ListCSVURL[i][1], tempFolder + "\\" + ListCSVURL[i][0] + ".csv");
            }

            {
                DirectoryInfo di2 = new DirectoryInfo(SlimeFolderPath + @"\Unity_Assets_Files");
                if (di2.Exists == false)
                {
                    di2.Create();
                }
                else
                {
                    Directory.Delete(SlimeFolderPath + @"\Unity_Assets_Files", true);
                    di2.Create();
                }
            }

            {
                System.Diagnostics.Process ps = new System.Diagnostics.Process();
                ps.StartInfo.FileName = currentDirectory + @"\ExtractText.exe";
                ps.StartInfo.Arguments = "\"" + currentDirectory + "\" \"" + SlimeFolderPath + "\"";
                ps.StartInfo.WorkingDirectory = currentDirectory;
                ps.Start();
                ps.WaitForExit();
                System.Threading.Thread.Sleep(5 * 1000);
            }

            for (int i = 0; i < ListCSVURL.Count; i++)
            {
                string OriginalTXTPath = SlimeFolderPath + @"\Unity_Assets_Files\resources\";
                int ResFileNum = findResFileNum[Array.IndexOf(findResFileName, ListCSVURL[i][0])];
                if (ResFileNum == 0)
                {
                    OriginalTXTPath += ListCSVURL[i][0] + ".txt";
                }
                else
                {
                    OriginalTXTPath += ListCSVURL[i][0] + "_" + ResFileNum.ToString("D5") + ".txt";
                }
                string TranslatedCSVPath = currentDirectory + "\\" + tempFolder + "\\" + ListCSVURL[i][0] + ".csv";
                System.Diagnostics.Process ps2 = new System.Diagnostics.Process();
                ps2.StartInfo.FileName = currentDirectory + @"\TXTCSVParser.exe";
                ps2.StartInfo.Arguments = "-Patch \"" + OriginalTXTPath + "\" \"" + TranslatedCSVPath + "\"";
                ps2.StartInfo.WorkingDirectory = currentDirectory;
                ps2.Start();
                ps2.WaitForExit();
            }

            {
                System.Diagnostics.Process ps = new System.Diagnostics.Process();
                ps.StartInfo.FileName = currentDirectory + @"\ImportTextFile.exe";
                ps.StartInfo.Arguments = "\"" + currentDirectory + "\" \"" + SlimeFolderPath + "\"";
                ps.StartInfo.WorkingDirectory = currentDirectory;
                ps.Start();
                ps.WaitForExit();
                System.Threading.Thread.Sleep(5 * 1000);
            }


            {
                System.Diagnostics.Process ps = new System.Diagnostics.Process();
                ps.StartInfo.FileName = currentDirectory + @"\FileIDExtractor.exe";
                ps.StartInfo.Arguments = "\"" + SlimeFolderPath + "\"";
                ps.StartInfo.WorkingDirectory = currentDirectory;
                ps.Start();
                ps.WaitForExit();
            }

            {
                System.Diagnostics.Process ps = new System.Diagnostics.Process();
                ps.StartInfo.FileName = currentDirectory + @"\MonoBehaviorExtractor.exe";
                ps.StartInfo.Arguments = "\"" + SlimeFolderPath + "\"";
                ps.StartInfo.WorkingDirectory = currentDirectory;
                ps.Start();
                ps.WaitForExit();
            }

            string FileIDFileName = @"FileID.txt";
            string FileIDString = System.IO.File.ReadAllText(FileIDFileName);
            FileIDString = FileIDString.Replace("\r", "");
            string[] splitedFileID = FileIDString.Split('\n');
            List<string[]> FileIDList = new List<string[]>();
            for (int i = 0; i < 10; i++)
            {
                FileIDList.Add(splitedFileID[i].Split(':'));
            }
            string FileIDArrayed = "";
            for (int i = 0; i < 10; i++)
            {
                FileIDArrayed += FileIDList[i][1] + " ";
            }
            FileIDArrayed = FileIDArrayed.Substring(0, FileIDArrayed.Length - 1);
            {
                DirectoryInfo di = new DirectoryInfo(currentDirectory + @"\..\resources_patch");
                if (di.Exists == false)
                {
                    di.Create();
                }
                else
                {
                    Directory.Delete(currentDirectory + @"\..\resources_patch", true);
                    di.Create();
                }
            }
            {
                System.Diagnostics.Process ps = new System.Diagnostics.Process();
                ps.StartInfo.FileName = currentDirectory + @"\Au3TextDatExtract.exe";
                ps.StartInfo.Arguments = FileIDArrayed;
                ps.StartInfo.WorkingDirectory = currentDirectory;
                ps.Start();
                ps.WaitForExit();
            }

            string resourses_patch_list = "";
            for (int i = 0; i < 10; i++)
            {
                resourses_patch_list += "resources_patch\\Raw_0_" + FileIDList[i][1] + ".dat\r\n";
            }
            resourses_patch_list = resourses_patch_list.Substring(0, resourses_patch_list.Length - 2);
            System.IO.File.WriteAllText(currentDirectory + @"\..\resources_patch\resourses_patch_list.txt", resourses_patch_list);

            {
                System.Diagnostics.Process ps = new System.Diagnostics.Process();
                ps.StartInfo.FileName = currentDirectory + @"\sharedassets0Editor.exe";
                ps.StartInfo.WorkingDirectory = currentDirectory;
                ps.Start();
                ps.WaitForExit();
            }

            if(DropboxFolderPath != "")
            {
                {
                    string tempRemoveFolder = DropboxFolderPath + @"\resources_patch";
                    DirectoryInfo di = new DirectoryInfo(tempRemoveFolder);
                    if (di.Exists == false)
                    {
                        di.Create();
                    }
                    else
                    {
                        Directory.Delete(tempRemoveFolder, true);
                        di.Create();
                    }
                }
                {
                    string tempRemoveFolder = DropboxFolderPath + @"\sharedassets0_patch";
                    DirectoryInfo di = new DirectoryInfo(tempRemoveFolder);
                    if (di.Exists == false)
                    {
                        di.Create();
                    }
                    else
                    {
                        Directory.Delete(tempRemoveFolder, true);
                        di.Create();
                    }
                }
                CopyFolder(currentDirectory + @"\..\resources_patch", DropboxFolderPath + @"\resources_patch");
                CopyFolder(currentDirectory + @"\..\sharedassets0_patch", DropboxFolderPath + @"\sharedassets0_patch");
            }
        }

        static void UpdateWork()
        {
            string currentDirectory = System.IO.Directory.GetCurrentDirectory();
            string CSVURLString = System.IO.File.ReadAllText(@"CSVURL.txt");
            CSVURLString = CSVURLString.Replace("\r", "");
            string[] CSVURL = CSVURLString.Split('\n');
            List<string[]> ListCSVURL = new List<string[]>();
            for (int i = 0; i < CSVURL.Length; i++)
            {
                ListCSVURL.Add(CSVURL[i].Split('\\'));
            }
            string tempFolder = @"temp";
            {
                DirectoryInfo di = new DirectoryInfo(tempFolder);
                if (di.Exists == false)
                {
                    di.Create();
                }
                else
                {
                    Directory.Delete(tempFolder, true);
                    di.Create();
                }
            }

            string[] findResFileName = { "achieve", "actor", "exchange", "global", "keys", "mail", "pedia", "range", "tutorial", "ui" };
            int[] findResFileNum = { 2, 1, 3, 0, 1, 0, 2, 4, 1, 1 };

            for (int i = 0; i < ListCSVURL.Count; i++)
            {
                WebClient webClient = new WebClient();
                webClient.DownloadFile(ListCSVURL[i][1], tempFolder + "\\" + ListCSVURL[i][0] + ".csv");
            }

            {
                DirectoryInfo di2 = new DirectoryInfo(SlimeFolderPath + @"\Unity_Assets_Files");
                if (di2.Exists == false)
                {
                    di2.Create();
                }
                else
                {
                    Directory.Delete(SlimeFolderPath + @"\Unity_Assets_Files", true);
                    di2.Create();
                }
            }

            {
                System.Diagnostics.Process ps = new System.Diagnostics.Process();
                ps.StartInfo.FileName = currentDirectory + @"\ExtractText.exe";
                ps.StartInfo.Arguments = "\"" + currentDirectory + "\" \"" + SlimeFolderPath + "\"";
                ps.StartInfo.WorkingDirectory = currentDirectory;
                ps.Start();
                ps.WaitForExit();
            }

            {
                DirectoryInfo di2 = new DirectoryInfo(currentDirectory + @"\UpdatedCSVFiles");
                if (di2.Exists == false)
                {
                    di2.Create();
                }
                else
                {
                    Directory.Delete(currentDirectory + @"\UpdatedCSVFiles", true);
                    di2.Create();
                }
            }

            for (int i = 0; i < ListCSVURL.Count; i++)
            {
                string OriginalTXTPath = SlimeFolderPath + @"\Unity_Assets_Files\resources\";
                int ResFileNum = findResFileNum[Array.IndexOf(findResFileName, ListCSVURL[i][0])];
                if (ResFileNum == 0)
                {
                    OriginalTXTPath += ListCSVURL[i][0] + ".txt";
                }
                else
                {
                    OriginalTXTPath += ListCSVURL[i][0] + "_" + ResFileNum.ToString("D5") + ".txt";
                }
                string TranslatedCSVPath = currentDirectory + "\\" + tempFolder + "\\" + ListCSVURL[i][0] + ".csv";
                System.Diagnostics.Process ps2 = new System.Diagnostics.Process();
                ps2.StartInfo.FileName = currentDirectory + @"\TXTCSVParser.exe";
                ps2.StartInfo.Arguments = "-Update \"" + OriginalTXTPath + "\" \"" + TranslatedCSVPath + "\" \"" + currentDirectory + @"\UpdatedCSVFiles\" + ListCSVURL[i][0] + ".csv\"";
                ps2.StartInfo.WorkingDirectory = currentDirectory;
                ps2.Start();
                ps2.WaitForExit();
            }
        }
    }
}
