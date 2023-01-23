using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ParentObj : MonoBehaviour
{
    Board board;
    gamemanager game;
    public GameObject RootObject;


    private void Start()
    {
        board = GameObject.FindObjectOfType<Board>();
        game = GameObject.FindObjectOfType<gamemanager>();
    }
    public void Parent()
    {
        if (game.rotechng==true)
        {
            gameObject.transform.parent = RootObject.gameObject.transform;
        }
        else
        {
            return;
        }

    }
}
