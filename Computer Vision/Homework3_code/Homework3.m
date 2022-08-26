function main = main(image1,image2,inliers, threshold)
    arguments
    image1 string = "uttower_left.jpg";
    image2 string = "uttower_right.jpg";
    inliers string = "17";
    threshold string = "10";
    end
    inliers = str2double(inliers);
    threshold = str2double(threshold);
    f1 = figure('Name',"Left Harris");
    f2 = figure('Name',"Right Harris");
    f3 = figure('Name',"Left NMS");
    f4 = figure('Name',"Right NMS");
    f5 = figure('Name',"Patch Similarity");
    f6 = figure('Name',"Warped Image for 20 points");
    f7 = figure('Name',"Warped Image for 50 points");
    

    %Read images and find harris (1a)
    image1 = imread(image1);
    image2 = imread(image2);
    image1g = rgb2gray(image1);
    image2g = rgb2gray(image2);
    harris1 = harrisdetector(double(image1g));
    harris2 = harrisdetector(double(image2g));
    
    figure(f1);
    imshow(harris1);
    figure(f2);
    imshow(harris2);
    
    % Do nms (1b)
    maxima1 = maxes(harris1);
    maxima2 = maxes(harris2);
    answer1 = non_maxsuppression(maxima1);
    answer2 = non_maxsuppression(maxima2);
    
    figure(f3);
    imshow(answer1);
    figure(f4);
    imshow(answer2);
    
    %Do matching on images (1c)
    points1 = getpoints(answer1);
    points2 = getpoints(answer2);
    [pointsleft,pointsright,pointsall] = ssd_patch(image1g,image2g,points1,points2,40);
    figure(f5);
    showMatchedFeatures(image1,image2,pointsleft,pointsright,'montage');
    
    %Get Random points (2a)
    pointsrandom = correspondences(pointsall);
    disp(pointsrandom);
    
    %Find Affine transformation (2b)
    pointsall = pointsall(1:20,1:4);
    [Affine,Average,Inliers,Iter] = ransac(pointsall,inliers,threshold);
    disp(Affine);
    disp(Average);
    disp(Inliers);
    disp(Iter);
    
    pointsall = cat(1,pointsall,pointsrandom(1:30,1:4));
    [AffineR,AverageR,InliersR,IterR] = ransac(pointsall,inliers,threshold);
    disp(AffineR);
    disp(AverageR);
    disp(InliersR);
    disp(IterR);
    

    %Warp Image (2c)
    
    warped = warp(image1, image2, Affine);
    figure(f6);
    imshow(uint8(warped));
    
    
    warpedR = warp(image1, image2, AffineR);
    figure(f7);
    imshow(uint8(warpedR));
end
%Reused code
%Pads Matrix
function padded_array = pad(image,sigma)
    %original rows, original colums
    [or,oc] = size(image);
    new_sigma = 3*sigma;
    m = zeros(or+(2*new_sigma), oc+(2*new_sigma), "double");
    m(new_sigma+1:or+new_sigma,new_sigma+1:oc+new_sigma)=image;
    
    %Top Left Corner
    for r = 1:new_sigma+1
        for c = 1:new_sigma+1
            m(r,c) = m(new_sigma+1,new_sigma+1);
       end
    end
    %Left side
    for r = new_sigma+1:or+new_sigma-1
        for c = 1:new_sigma+1
            m(r,c) = m(r,new_sigma+1);
        end
    end
     %Bottom Left Corner
     for r = or+new_sigma:or+(2*new_sigma)
        for c = 1:new_sigma+1
            m(r,c) = m(or+new_sigma,new_sigma+1);
       end
    end
     %Top
    for r = 1:new_sigma
         for c = new_sigma+1:oc+new_sigma
             m(r,c) = m(new_sigma+1,c);
         end
     end
     %Top Right Corner
     for r = 1:new_sigma+1
        for c = oc+new_sigma+1:oc+(2*new_sigma)
             m(r,c) = m(new_sigma+1,oc+new_sigma);
        end
     end
     %Right Side
     for r = new_sigma+1:or+new_sigma-1
         for c = oc+new_sigma+1:oc+(2*new_sigma)
             m(r,c) = m(r,oc+new_sigma);
         end
     end
     %Bottom Right Corner
     for r = or+new_sigma:or+(2*new_sigma)
         for c = oc+new_sigma+1:oc+(2*new_sigma)
             m(r,c) = m(or+new_sigma,oc+new_sigma);
        end
     end
     %Bottom
     for r = or+new_sigma:or+(2*new_sigma)
         for c = new_sigma+1:oc+new_sigma
             m(r,c) = m(or+new_sigma,c);
        end
     end
    padded_array=m;
    
end

%Applies any filter to an image
%Takes in a filter, image, and the extended image
function apply_filter = app(filter,image,ext_image)
    [row,col] = size(image);
    [re,ce] = size(ext_image);
    [~,len] = size(filter);
    newx = re - row;
    newy = ce - col;
    image2 = zeros(row, col);
    for r = 1:row
        for c = 1:col
            newr = r +((newx)/2);
            newc = c +((newy)/2);
            piece = ext_image((newr)-((len-1)/2):(newr)+((len-1)/2),(newc)-((len-1)/2):(newc)+((len-1)/2));
            %mult_matrix = mult_matrices(filter,piece);
            mult_matrix = filter .* piece;
            image2(r,c) = sum(mult_matrix(:));
        end
    end
    apply_filter = image2;
end



%Gets the Gaussian Filter
function get_gaussian = gauss(sigma)
   size = 6*sigma;
   filter = zeros(size-1,size-1);
   for r = 1:size-1
        for c = 1:size-1
             x = abs(r - size/2);
             y = abs(c - size/2);
             filter(r,c) = (1/(2*pi*sigma))*exp((-(x^2 + y^2))/(2*sigma^2));
        end
   end
   sumof = sum(filter(:));
   get_gaussian = filter;
end

%Applies the Gaussian filter
function appgauss = appgauss(image,sigma)
    %Do the Gauss
     gaussian = gauss(sigma);
     padded_matrix = pad(image,sigma);
     appgauss = app(gaussian,image,padded_matrix);
end

%Applies the Vertical Sobel Filter
function sob1 = sobel1(gaussimage)
     single_pad = pad(gaussimage,1);
     sobelfilt1 = [-1 0 1; -2 0 2; -1 0 1];
     sob1 = app(sobelfilt1,gaussimage,single_pad);
     sob1 = double(sob1);
     
end

%Applies the Horizontal Sobel Filter
function sob2 = sobel2(gaussimage)
     single_pad = pad(gaussimage,1);
     sobelfilt2 = [1 2 1; 0 0 0; -1 -2 -1];
     sob2 = app(sobelfilt2,gaussimage,single_pad);
     sob2 = double(sob2);
end

%Parts 1 a/b
function harris = harrisdetector(image)
    gaussimage = appgauss(image,3);
    [row,col] = size(image);
    sobx = sobel1(gaussimage);
    sobxx = sobel1(sobx);
    soby = sobel2(gaussimage);
    sobyy = sobel2(soby);
    sobxy = sobel2(sobx);
    image2 = zeros(row, col);
    for r = 1:row
        for c = 1:col
            mm = gaussimage(r,c) * [sobxx(r,c) sobxy(r,c); sobxy(r,c) sobyy(r,c)];
            image2(r,c) = det(mm) - (.05*(trace(mm)^2));
        end
    end
    harris = image2;
end

function maximum = maxes(harris)
    [row,col] = size(harris);
    image2 = zeros(row, col);
    count = 0;
    while(count < 1000)
        biggest = max(harris(:));
        for r= 1:row
            for c = 1:col
                if(harris(r,c) == biggest)
                    image2(r,c) = biggest;
                    harris(r,c) = 0;
                    count= count + 1;
                    r=row;
                    break;
                end
            end
        end
    end
    maximum = image2;
end

function non_max = non_maxsuppression(image)
    [row,col] = size(image);
    m = zeros(row,col, "double");
    image = pad(image,(1/3));
    for r = 2:row+1
         for c= 2:col+1
             if(max(image(r-1:r+1,c-1:c+1), [], 'all') == image(r,c))
                    m(r-1,c-1) = image(r,c);
                 else
                    m(r-1,c-1) = 0;
             end
         end
    end
    non_max = m;
end

function getpoints = getpoints(matrix)
    [row,col] = size(matrix);
    getpoints = [];
    for r= 1:row
        for c = 1:col
            if(matrix(r,c) ~= 0)
                getpoints = cat(1,getpoints,[r c]);
                
            end
        end
    end
end

%Part 1c

function [pointsleft,pointsright,pointsall] = ssd_patch(image1,image2,points1,points2,r)
    [row1,~] = size(points1);
    [row2,~] = size(points2);
    pointsall = [];
    harris1 = pad(image1,r/3);
    harris2 = pad(image2,r/3);
     for r1= 1:row1
        for r2 = 1:row2
            p1 = points1(r1,1:2);
            p2 = points2(r2,1:2);
            patch1 = harris1((p1(1)+r)-r:(p1(1)+r)+r,(p1(2)+r)-r:(p1(2)+r)+r);
            patch2 = harris2((p2(1)+r)-r:(p2(1)+r)+r,(p2(2)+r)-r:(p2(2)+r)+r);
            X=patch1-patch2;
            ssd = sum(X(:).^2);
            p1 = p1(end:-1:1);
            p2 = p2(end:-1:1);
            combined = cat(2,p1,p2,ssd);
            pointsall = cat(1,pointsall,combined);
        end
     end
     pointsall = sortrows(pointsall,5);
     pointsleft = pointsall(1:20,1:2);
     pointsright = pointsall(1:20,3:4);
     
    
end

%Part 2a
function pointsrandom = correspondences(pointsall)
    pointsrandom = [];
    [row,~] = size(pointsall);
    for i = 1:30
        r = randi(row);
        pointsrandom = cat(1,pointsrandom,pointsall(r,1:end));
    end
end

%Part 2b
function [RANSAC,average,inlierlist,iter] = ransac(pointsall,inliers,threshold) 
    iter = 0;
    while(1==1)
        inlierlist = [];
        inliersc = 0;
        points = [];
        [row,~] = size(pointsall);
        r = randperm(row,3);
        points = cat(1,points,pointsall(r(1),1:4));
        points = cat(1,points,pointsall(r(2),1:4));
        points = cat(1,points,pointsall(r(3),1:4));
        A = [points(1,1) points(1,2) 1 0 0 0;
                0 0 0 points(1,1) points(1,2) 1;
                points(2,1) points(2,2) 1 0 0 0;
                0 0 0 points(2,1) points(2,2) 1;
                points(3,1) points(3,2) 1 0 0 0;
                0 0 0 points(3,1) points(3,2) 1];
        B = [points(1,3);
                points(1,4);
                points(2,3);
                points(2,4);
                points(3,3);
                points(3,4)];
        X= linsolve(A,B);
        %Apply to each first point, check distance between affined point and
        %second point
        totaldist = 0;
        for r = 1 : row
            first = [pointsall(r,1);
                    pointsall(r,2);
                    1];
            second = [X(1,1) X(2,1) X(3,1);
                      X(4,1) X(5,1) X(6,1)];
            point = second * first;
            distance = sqrt(((point(1,1) - pointsall(r,3))^2) + ((point(2,1) - pointsall(r,4))^2));
            if(distance < threshold)
                inliersc = inliersc + 1;
                combined = cat(2,pointsall(r,3),pointsall(r,4));
                inlierlist = cat(1,inlierlist,combined);
                totaldist = totaldist + distance;
            end
        end
        iter = iter + 1;
        if(inliersc >= inliers)
            RANSAC = X;
            average = totaldist/inliersc;
            break;
        end
    end       
end


function warped = warp(image1, image2, affine)
    change = maketform('affine', [affine(1,1) affine(4,1) 0; affine(2,1) affine(5,1) 0; affine(3,1) affine(6,1) 1]);
    [transformation, x, y] = imtransform(image1,change); 
    [row, col,~] = size(image2);
    [rowt, colt,~] = size(transformation);
    xshift = ceil(abs(x(1)));
    yshift = ceil(abs(y(1)));
    newimage = zeros(row+yshift,col+xshift,3,'uint8');
    newimage(yshift+1:end,xshift+1:end,:) = image2;
    
    for r = 1:rowt
        for c = 1:colt
            if(transformation(r,c,:) == [0 0 0])
            
            else
                if(newimage(r,c,:) == [0 0 0])
                    newimage(r,c,:) = transformation(r,c,:);
                else
                    newimage(r,c,:) = (transformation(r,c,:) .* (.5)) + (newimage(r,c,:) .* (.5));
                end
            
            end
            
                
        end
    end
    warped = newimage;

end


