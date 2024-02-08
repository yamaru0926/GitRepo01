Module modRegistry

    Friend Const REG_STATEMACHINESIM_KEY As String = "Software\ARTiSAN Software Tools\StateMachineSim"

    Friend Function fAutoLaunch() As Boolean

        Dim oCurrentUser As Microsoft.Win32.RegistryKey = Microsoft.Win32.Registry.CurrentUser
        Dim oStateMachineSimKey As Microsoft.Win32.RegistryKey

        oStateMachineSimKey = oCurrentUser.OpenSubKey("Software\ARTiSAN Software Tools\StateMachineSim", False)

        If (IsNothing(oStateMachineSimKey)) Then
            Return True

        Else

            With oStateMachineSimKey

                If Not (IsNothing(.GetValue("AutoLaunch"))) Then
                    If (.GetValue("AutoLaunch") = 0) Then
                        Return False
                    End If
                End If

            End With

        End If

        Return True

    End Function

    Friend Sub pSetAutoLaunch(ByVal bAutoLaunch As Boolean)

        Dim oCurrentUser As Microsoft.Win32.RegistryKey = Microsoft.Win32.Registry.CurrentUser
        Dim oStateMachineSimKey As Microsoft.Win32.RegistryKey

        oStateMachineSimKey = oCurrentUser.OpenSubKey(REG_STATEMACHINESIM_KEY, True)

        If (oStateMachineSimKey Is Nothing) Then
            oStateMachineSimKey = oCurrentUser.CreateSubKey(REG_STATEMACHINESIM_KEY, Microsoft.Win32.RegistryKeyPermissionCheck.Default)
        End If

        With oStateMachineSimKey

            If (bAutoLaunch) Then
                .SetValue("AutoLaunch", 1)
            Else
                .SetValue("AutoLaunch", 0)
            End If

        End With

    End Sub
End Module
