using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ParentObjeLift : MonoBehaviour
{
    Board board;
    gamemanager game;

    private void Start()
    {
        board = GameObject.FindObjectOfType<Board>();
        game = GameObject.FindObjectOfType<gamemanager>();
    }
    public void ParentLift()
    {
        if (game.rotechng == true)
        {
           
            board.gameObject.transform.parent = null;
        }
        else
        {
            return;
        }

    }
}
