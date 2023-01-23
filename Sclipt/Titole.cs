using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Titole : MonoBehaviour
{
    

    
    void Update()
    {
        if (Input.GetKey("joystick button 2"))
            {
            SceneManager.LoadScene(1);
            }
    }
}
