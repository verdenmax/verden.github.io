import numpy as np

def ho_kashyap_algorithm(Y, eta=0.1, bmin=1e-5, kmax=100000):

    n_samples = X.shape[0]
    a = np.array([[0.35],[-0.25],[0.48]])  # Initialize weights
    b = np.ones((X.shape[0],1))
    k = 0                    # Iteration counter


    print(Y@a)
    return
    while k < kmax:
        k += 1

        e = (np.dot(Y, a) - b)  # Calculate the error
        e_plus = 0.5 * (e + np.abs(e))  # Apply the positive part

        # Update bias
        b += 2 * eta * e_plus

        # Update weights
        YN = np.linalg.pinv(Y)
        a = YN@b

        # Check for convergence
        if np.max(np.abs(e)) <= bmin:
            return Y@a  # Return weights and bias if converged

    print("No solution found!")
    return Y@a

if __name__ == "__main__":
     #数据一
    X_x = np.array([[0.1, 1.1],
                    [6.8, 7.1],
                    [-3.5, -4.1],
                    [2.0, 2.7],
                    [4.1, 2.8],
                    [3.1, 5.0],
                    [-0.8, -1.3],
                    [0.9, 1.2],
                    [5.0, 6.4],
                    [3.9, 4.0]])
     #数据三
    X_y = np.array([
            [-3.0,-2.9],
            [0.5,8.7],
            [2.9,2.1],
            [-0.1,5.2],
            [-4.0,2.2],
            [-1.3,3.7],
            [-3.4,6.2],
            [-4.1,3.4],
            [-5.1,1.6],
            [1.9,5.1],])


    # # 数据二
    # X_x = np.array([[7.1, 4.2],
    #                 [-1.4, -4.3],
    #                 [4.5, 0.0],
    #                 [6.3, 1.6],
    #                 [4.2, 1.9],
    #                 [1.4, -3.2],
    #                 [2.4, -4.0],
    #                 [2.5, -6.1],
    #                 [8.4, 3.7],
    #                 [4.1, -2.2]])
    #
    # # 数据四
    #
    # X_y = np.array([
    #             [-2.0,-8.4],
    #             [-8.9,0.2],
    #             [-4.2,-7.7],
    #             [-8.5,-3.2],
    #             [-6.7,-4.0],
    #             [-0.5,-9.2],
    #             [-5.3,-6.7],
    #             [-8.7,-6.4],
    #             [-7.1,-9.7],
    #             [-8.0,-6.3],
    #                     ])

    # Combine the datasets
    X = np.vstack((X_x, -X_y))

    # Create labels: +1 for X_x, -1 for X_y
    Y = np.ones(X_x.shape[0])  # Labels for X_x
    Y = np.concatenate((Y, -1 * np.ones(X_y.shape[0])))  # Labels for X_y

    Y_full = np.hstack((X, Y.reshape(-1, 1)))  # Combine features and labels

    a = ho_kashyap_algorithm( Y_full)

    print("分类结果:", a)
