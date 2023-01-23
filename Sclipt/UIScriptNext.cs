using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;


public class UIScriptNext : MonoBehaviour
{
    [SerializeField]
    public Sprite title_0;
    [SerializeField]
    public Sprite title_1;
    [SerializeField]
    public Sprite title_2;
    [SerializeField]
    public Sprite title_3;
    [SerializeField]
    public Sprite title_4;
    [SerializeField]
    public Sprite title_5;
    [SerializeField]
    public Sprite title_6;
    public Image image;
    private Sprite sprite;
    Spawner spawner;
    // Update is called once per frame
    void Start()
    {
        spawner = GameObject.FindObjectOfType<Spawner>();//スポナークラスからブロック生成関数を読んで半数に格納する
    }
    public void SpriteNext()
    {
        switch (spawner.next2)
        {
            case 0:
            sprite = title_0;
            image = this.GetComponent<Image>();
            image.sprite = sprite;
            break;

            case 1:
            sprite = title_1;
            image = this.GetComponent<Image>();
            image.sprite = sprite;
            break;

            case 2:
            sprite = title_2;
            image = this.GetComponent<Image>();
            image.sprite = sprite;
            break;

            case 3:
            sprite = title_3;
            image = this.GetComponent<Image>();
            image.sprite = sprite;
            break;

            case 4:
            sprite = title_4;
            image = this.GetComponent<Image>();
            image.sprite = sprite;
            break;

            case 5:
            sprite = title_5;
            image = this.GetComponent<Image>();
            image.sprite = sprite;
            break;

            case 6:
            sprite = title_6;
            image = this.GetComponent<Image>();
            image.sprite = sprite;
            break;
        }

    }

}
