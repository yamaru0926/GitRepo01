Option Strict Off
Option Explicit On

Friend Class Form1

    Inherits System.Windows.Forms.Form

    Public Enum LightType
        Red
        Green
        Amber
        None
    End Enum

    Dim sim As Object
    Dim hSM As Integer
    Dim bPress As Boolean
    Dim objBrush As New SolidBrush(Color.Black)
    Dim enumLight As LightType = LightType.None
    Dim boolWinApp As Boolean = False

    Private redRectangle As New Rectangle(40, 24, 33, 33)
    Private greenRectangle As New Rectangle(40, 104, 33, 33)
    Private amberRectangle As New Rectangle(40, 64, 33, 33)

    Private objProcess As Diagnostics.Process = New Diagnostics.Process

    Private Sub Form1_FormClosed(ByVal eventSender As System.Object, ByVal eventArgs As System.Windows.Forms.FormClosedEventArgs) Handles Me.FormClosed

        Try

            If Not sim Is Nothing Then
                sim.UnloadStateMachine("")
                sim = Nothing
            End If

        Catch
        End Try

    End Sub

    Private Sub Command1_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles Command1.Click

        'using Inject here can fail due already being in an Automation call
        bPress = True

    End Sub

    Private Sub RtS_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles RtS.Click

        Try

            If (sim Is Nothing) Then

                sim = CreateObject("Studio.StateMachineController")
                If Not (sim Is Nothing) Then

                    With sim
                        .EnableAnimation()
                        .EnableEventQueuing()
                        .ResetDiagrams() 'clear existing highlights
                        .SetForegroundWindow() 'bring RtS to the front
                    End With

                    If (fAutoLaunch()) Then
                        RunWinappBackgroundWorker.RunWorkerAsync(boolWinApp)
                    End If

                    Activate() 'put our window on top
                    hSM = sim.CreateStateMachine("")

                    If hSM <> 0 Then
                        Timer1.Enabled = True
                        RtS.Text = "Stop"
                    Else
                        MsgBox("Failed to load harness DLL")
                        sim = Nothing
                    End If

                End If

            Else

                Timer1.Enabled = False

                If (fAutoLaunch()) Then
                    With objProcess
                        .StandardInput.Write(vbNewLine)
                        .WaitForExit()
                    End With
                End If

                RtS.Text = "Start"

            End If

            Autolaunch.Enabled = False

        Catch
            sim = Nothing
        End Try

    End Sub

    Private Sub Off_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles Off.Click 'example of Injecting an event with parameters

        If Not sim Is Nothing Then

            If Off.Text = "Off" Then
                sim.SetParameterCount(2)
                sim.SetParameter(0, "1")
                sim.SetParameter(1, "a")
                sim.InjectEvent(hSM, "Deactivate")
                Off.Text = "On"

            Else
                sim.InjectEvent(hSM, "Activate")
                Off.Text = "Off"

            End If

        End If

    End Sub

    Private Function fRunCmdLineApp() As Boolean

        Dim strFileName As String = "..\release\WinApp.exe"

        Try
            Dim strOutput As String = Nothing

            With objProcess
                .StartInfo.FileName = strFileName
                .StartInfo.CreateNoWindow = True
                .StartInfo.UseShellExecute = False
                .StartInfo.RedirectStandardInput = True
                .Start()
            End With

            Return True

        Catch ex As Exception
            MsgBox("ERROR: " & ex.Message)
            Return False
        End Try

    End Function

    Private Sub Timer1_Tick(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles Timer1.Tick

        Dim obname As Object
        Dim none As Boolean

        none = False

        While (Not sim Is Nothing) And (Not none)

            If bPress Then
                bPress = False
                sim.InjectEvent(hSM, "ButtonPress")
            End If

            If sim.GetNextEvent() Then
                obname = sim.GetEventName()
                Message.Text = obname

                If sim.GetParameterCount() = 1 Then

                    If sim.GetParameter(0) = "1" Then
                        'Light on

                        Select Case (obname)

                            Case "Lights.Red"
                                objBrush.Color = Color.Red
                                enumLight = LightType.Red
                                Me.Invalidate(redRectangle)

                            Case "Lights.Amber"
                                objBrush.Color = Color.FromArgb(255, 128, 0)
                                enumLight = LightType.Amber
                                Me.Invalidate(amberRectangle)

                            Case "Lights.Green"
                                objBrush.Color = Color.Lime
                                enumLight = LightType.Green
                                Me.Invalidate(greenRectangle)

                            Case "Lights.Wait"
                                WaitLight.ForeColor = System.Drawing.ColorTranslator.FromOle(&HFFFFFF)

                        End Select

                    Else

                        Select Case (obname)

                            Case "Lights.Red"
                                objBrush.Color = Color.Maroon
                                Me.Invalidate(redRectangle)

                            Case "Lights.Amber"
                                objBrush.Color = Color.FromArgb(128, 64, 0)
                                Me.Invalidate(amberRectangle)

                            Case "Lights.Green"
                                objBrush.Color = Color.Green
                                Me.Invalidate(greenRectangle)

                            Case "Lights.Wait"
                                WaitLight.ForeColor = System.Drawing.ColorTranslator.FromOle(&H808080)

                        End Select
                        enumLight = LightType.None

                    End If

                End If

            Else
                none = True
            End If


            System.Windows.Forms.Application.DoEvents()

        End While

    End Sub

    Private Sub Autolaunch_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Autolaunch.CheckedChanged
        pSetAutoLaunch(Autolaunch.Checked)
    End Sub

    Private Sub Form1_Load(ByVal sender As Object, ByVal e As System.EventArgs) Handles Me.Load
        Autolaunch.Checked = fAutoLaunch()
    End Sub

    Private Sub Form1_Paint(ByVal sender As Object, ByVal e As System.Windows.Forms.PaintEventArgs) Handles Me.Paint

        'Trunk
        Dim objGraphics As Graphics = e.Graphics
        Dim objRect As New Rectangle(48, 152, 17, 129)
        Dim objStaticBrush As New SolidBrush(Color.Black)
        objGraphics.FillRectangle(objStaticBrush, objRect)

        'Platform
        objRect.X = 24
        objRect.Y = 8
        objRect.Width = 65
        objRect.Height = 145
        objGraphics.FillRectangle(objStaticBrush, objRect)

        'Pedestrian display
        objRect.X = 37
        objRect.Y = 200
        objRect.Width = 39
        objRect.Height = 43
        objStaticBrush.Color = Color.FromArgb(192, 192, 192)
        objGraphics.FillRectangle(objStaticBrush, objRect)


        Select Case enumLight

            Case LightType.Red
                'Red light
                objGraphics.FillEllipse(objBrush, redRectangle)

            Case LightType.Green
                'Green light
                objGraphics.FillEllipse(objBrush, greenRectangle)

            Case LightType.Amber
                'Amber light
                objGraphics.FillEllipse(objBrush, amberRectangle)

            Case Else
                'Red light. Background
                objBrush.Color = Color.Maroon
                objGraphics.FillEllipse(objBrush, redRectangle)

                'Green light. Background
                objBrush.Color = Color.Green
                objGraphics.FillEllipse(objBrush, greenRectangle)

                'Amber light. Background
                objBrush.Color = Color.FromArgb(128, 64, 0)
                objGraphics.FillEllipse(objBrush, amberRectangle)

        End Select

    End Sub

    Private Sub RunWinappBackgroundWorker_DoWork(sender As System.Object, e As System.ComponentModel.DoWorkEventArgs) Handles RunWinappBackgroundWorker.DoWork
        Threading.Thread.Sleep(2000)
        boolWinApp = fRunCmdLineApp()
        If (Not boolWinApp) Then
            MsgBox("Failed to automatically launch Winapp.exe")
        End If
    End Sub
End Class